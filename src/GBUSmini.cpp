#include "GBUSmini.h"

uint8_t GBUS_send_request_ack(uint8_t pin, uint8_t to, uint8_t from, uint8_t tries, int timeout) {
    GBUS_send_request(pin, to, from);
    uint8_t thisTry = 0;
    uint32_t tmr = millis();
    while (1) {
        uint8_t addr = GBUS_read_ack(pin, from);
        if (addr == to) return ACK_ONLY;
        if (millis() - tmr >= timeout) {
            tmr = millis();
            thisTry++;
            if (thisTry >= tries) return ACK_ERROR;
            GBUS_send_request(pin, to, from);
        }
    }		
    return ACK_ERROR;
}

// *******************************************************
bool GBUS_is_busy(uint8_t pin) {
    static uint32_t tmr;
    if (digitalRead(pin)) {
        if (millis() - tmr >= GBUSMINI_BUSY_TIMEOUT) return false;
        else return true;
    } else {
        tmr = millis();
        return true;
    }
}

// *******************************************************
// ********************* ЧТЕНИЕ **************************
// *******************************************************
uint8_t GBUS_read_raw(uint8_t pin, uint8_t* buf, uint8_t size) {
    if (!digitalRead(pin)) {    	// проверяем старт бит (low)
        delayMicroseconds(GBUS_BIT_2);		// ждём половину времени
        if (!digitalRead(pin)) { 	// если всё ещё старт бит (low)
            int8_t bitCount = 0;	// счётчик битов
            uint8_t byteCount = 0;		// счётчик байтов
            while (1) {				
                delayMicroseconds(GBUS_BIT-GBUS_OFFSET_READ);	// ждём бит
                uint8_t bit = digitalRead(pin);					// читаем
                if (bitCount < 8) {								// передача битов даты
                    bitWrite(buf[byteCount], bitCount, bit);  	// пишем в буфер
                } else if (bitCount == 8) {						// стоп бит (high)
                    if (!bit) return 0;                   		// ошибка стоп бита. Завершаем
                    byteCount++;								// счётчик собранных байтов					
                } else if (bitCount == 9) {						// старт бит (low)					
                    if (bit) return byteCount;                	// не дождались старт бита. Конец приёма, возврат количества
                    if (byteCount >= size) return 0;        	// буфер переполнен. Завершаем
                    bitCount = -1;          					// костыль
                }
                bitCount++;										// следующий бит
            }
        }
    }
    return 0;
}


// *******************************************************
uint8_t GBUS_read(uint8_t pin, uint8_t addr, uint8_t* buf, uint8_t size) {
    uint8_t buf2[size + GBUS_OFFSET];									// буфер на приём
    uint8_t bytes = GBUS_read_raw(pin, buf2, (size + GBUS_OFFSET));	// принимаем, получаем количество байт посылки
    if (buf2[0] == bytes && (buf2[1] == addr || buf2[1] == 255)) {	// если совпало количество байт и адрес
#if (GBUS_CRC == 1)
        if (GBUS_crc_bytes(buf2, bytes) != 0) return 0;
#endif
        for (uint8_t i = 0; i < bytes - GBUS_OFFSET; i++) buf[i] = buf2[i + 3];	// переписываем в буфер в скетче
        return buf2[2];												// возвращаем адрес
    }
    return 0;														// иначе возвращаем ошибку
}

// *******************************************************
// структура буфера: [0, адрес получателя, адрес отправителя, CRC]
uint8_t GBUS_read_request(uint8_t pin, uint8_t addr) {
    uint8_t buf[GBUS_OFFSET];	
    if (GBUS_read_raw(pin, buf, GBUS_OFFSET) == GBUS_OFFSET 
            && (buf[1] == addr || buf[1] == 255)
#if (GBUS_CRC == 1)
    && GBUS_crc_bytes(buf, GBUS_OFFSET) == 0
#endif
    && buf[0] == 0) return buf[2];
    else return 0;
}

// *******************************************************
// структура буфера: [1, адрес получателя, адрес отправителя, CRC]
uint8_t GBUS_read_ack(uint8_t pin, uint8_t addr) {
    uint8_t buf[GBUS_OFFSET];	
    if (GBUS_read_raw(pin, buf, GBUS_OFFSET) == GBUS_OFFSET 
            && (buf[1] == addr || buf[1] == 255)
#if (GBUS_CRC == 1)
    && GBUS_crc_bytes(buf, GBUS_OFFSET) == 0
#endif
    && buf[0] == 1) return buf[2];
    else return 0;
}


// *******************************************************
// ******************** ОТПРАВКА *************************
// *******************************************************
void GBUS_send_raw(uint8_t pin, uint8_t* buf, uint8_t size) {
    for (uint8_t bytes = 0; bytes < size; bytes++) {
        for (int8_t bits = -1; bits < 9; bits++) {
            bool bit = 0;
            if (bits < 0) bit = 0;
            else if (bits < 8) bit = (buf[bytes] >> bits) & 1;
            else bit = 1;
            pinMode(pin, !bit);
            digitalWrite(pin, bit);
            delayMicroseconds(GBUS_BIT-GBUS_OFFSET_WRITE);
        }
    }
}

// *******************************************************
void GBUS_send(uint8_t pin, uint8_t to, uint8_t from, uint8_t* data, uint8_t size) {
    uint8_t buf[size + GBUS_OFFSET];
    uint8_t crc = 0;
    buf[0] = size + GBUS_OFFSET;
    buf[1] = to;
    buf[2] = from;
    for (uint8_t i = 0; i < size; i++) buf[i + 3] = data[i];
#if (GBUS_CRC == 1)
    buf[size + 3] = GBUS_crc_bytes(buf, size + 3);
#endif
    GBUS_send_raw(pin, buf, size+GBUS_OFFSET);
}

// *******************************************************
void GBUS_send_request(uint8_t pin, uint8_t to, uint8_t from) {
    uint8_t buf[GBUS_OFFSET] = {0, to, from};
#if (GBUS_CRC == 1)
    buf[3] = GBUS_crc_bytes(buf, 3);
#endif
    GBUS_send_raw(pin, buf, GBUS_OFFSET);
}

// *******************************************************
void GBUS_send_ack(uint8_t pin, uint8_t to, uint8_t from) {
    uint8_t buf[GBUS_OFFSET] = {1, to, from};
#if (GBUS_CRC == 1)
    buf[3] = GBUS_crc_bytes(buf, 3);
#endif
    GBUS_send_raw(pin, buf, GBUS_OFFSET);
}