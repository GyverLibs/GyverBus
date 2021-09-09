#include "GyverBus.h"

uint8_t packGBUScmd(uint8_t* buffer, uint8_t cmd, uint8_t to, uint8_t from) {
    buffer[0] = cmd;	// команда
    buffer[1] = to;		// адрес приёмника
    buffer[2] = from;	// адрес передатчика	
    if (GBUS_CRC) buffer[3] = GBUS_crc_bytes(buffer, 3);
    return GBUS_OFFSET;
}

GBUSstatus checkGBUS(uint8_t* buffer, uint8_t bufSize, uint8_t amount, uint8_t addr) {
    if (buffer[0] > bufSize) return RX_OVERFLOW;									// буфер переполнен
    if (amount > GBUS_OFFSET && amount > buffer[0]) return RX_OVERFLOW;				// пакет слишком большой
    if (buffer[1] != addr && buffer[1] != 255) return RX_ADDRESS_ERROR;				// не наш адрес
    if (amount < GBUS_OFFSET || (amount > GBUS_OFFSET && amount < buffer[0])) return RX_ABORT;		// передача прервана	
    if (GBUS_CRC) if (GBUS_crc_bytes(buffer, amount) != 0) return RX_CRC_ERROR;		// данные повреждены			
    if (buffer[0] == 0) return RX_REQUEST;											// реквест				
    if (buffer[0] == 1) return RX_ACK;												// подтверждение
    return RX_DATA;																	// данные приняты успешно
}

void GBUS_crc_update(uint8_t &crc, uint8_t data) {
#if defined (__AVR__)
    // резкий алгоритм для AVR
    uint8_t counter;
    uint8_t buffer;
    asm volatile (
    "EOR %[crc_out], %[data_in] \n\t"
    "LDI %[counter], 8          \n\t"
    "LDI %[buffer], 0x8C        \n\t"
    "_loop_start_%=:            \n\t"
    "LSR %[crc_out]             \n\t"
    "BRCC _loop_end_%=          \n\t"
    "EOR %[crc_out], %[buffer]  \n\t"
    "_loop_end_%=:              \n\t"
    "DEC %[counter]             \n\t"
    "BRNE _loop_start_%="
    : [crc_out]"=r" (crc), [counter]"=d" (counter), [buffer]"=d" (buffer)
    : [crc_in]"0" (crc), [data_in]"r" (data)
    );
#else
    // обычный для всех остальных
    uint8_t i = 8;
    while (i--) {
        crc = ((crc ^ data) & 1) ? (crc >> 1) ^ 0x8C : (crc >> 1);
        data >>= 1;
    }
#endif
}

uint8_t GBUS_crc_bytes(uint8_t *buffer, uint8_t size) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < size; i++) GBUS_crc_update(crc, buffer[i]);
    return crc;
}