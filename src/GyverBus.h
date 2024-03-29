/*
    GyverBus - библиотека для общения по протоколу GBUS
    Документация: https://alexgyver.ru/gyverbus/
    - Очень простой, надёжный, устойчивый к помехам и задержкам, но медленный интерфейс связи на базе UART
    - Двухсторонняя связь по одному проводу
    - Асинхронная отправка и чтение (на базе millis())
    - Двухсторонняя совместимость с аппаратным UART
    - Возможность принимать и отправлять данные внутри сети Ардуинок
    - Адресация до 254 устройств в сети (от 1 до 255)
    - Всеядная функция отправки и приёма (ест переменные, структуры, массивы)
    - Встроенная проверка CRC (контроль целостности) пакета данных
    - Возможность отправки и чтения короткого "запроса"
    - Поддерживаются все Arduino-совместимые платы
    - Сама библиотека предоставляет возможности по отладке (коды ошибок)
    - В примерах есть компактные варианты чтения и отправки данных, влезет даже в ATtiny
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    Версии:
    v1.1: добавлена waitAck() и исправлена ошибочка
    v1.2: улучшена стабильность, функции оптимизированы, уменьшен вес
    v1.3: добавлен CRC в запрос и ответ
    v2.0: 
        - Куча оптимизации
        - Логика работы переделана. Теперь GBUS работает для всех uart-библиотек
        - Однопроводной uart вынесен отдельным классом
        - Добавлена совместимость с esp8266
        - Переделана вся инициализация, смотри примеры!
        - Добавлены утилиты и примеры
    v2.1: вернул getStatus
    v2.2: небольшие багфиксы и оптимизация
    v2.3: добавлена возможность отправки широковещательного сообщения (всем), отправлять на адрес 255
    v2.4: исправлены ошибки, добавлена bool statusChanged() для GBUS
    v2.5: добавил пример с GyverTransfer, добавил смену адреса
*/

/*
    Что это и как работает?
    Библиотека GBUS.h позволяет общаться по протоколу GBUS через любой Stream-объект (Serial, SoftwareSerial, softUART и проч). Основное описание содержится в ней
    Библиотека GyverBus.h содержит базовые инструменты для упаковки и распаковки данных в байтовые пакеты с адресацией и CRC
    Библиотека softUART.h - это однопроводной UART, работающий на приём и отправку, причём не блокирующий выполнение кода
    Библиотека GBUSmini.h - это набор лёгких БЛОКИРУЮЩИХ функций для общения по одному проводу. Предусмотрено для мелких МК    
*/
#ifndef _GyverBus_h
#define _GyverBus_h
#include <Arduino.h>

// ============== НАСТРОЙКИ ============== 
#define GBUS_CRC 1                // 1 - вкл CRC, 0 - выкл (экономит память, но того не стоит)


// СТАТУСЫ (НЕ ТРОГАТЬ)
enum GBUSstatus {
    GBUS_IDLE,    
    TRANSMITTING,
    TX_OVERFLOW,    
    TX_COMPLETE,    
    RECEIVING,    
    RX_ERROR,
    RX_ABORT,
    RX_OVERFLOW,
    RX_ADDRESS_ERROR,    
    RX_CRC_ERROR,
    RX_REQUEST,    
    RX_DATA,
    RX_ACK,
};

// ============================ ВСЯКИЕ УТИЛИТЫ ============================

// =========== GBUS =========== 
// проверить статус принятых данных (буфер, его размер, кол-во принятых байтов, наш адрес)
// вернёт статус GBUSstatus
GBUSstatus checkGBUS(uint8_t* buffer, uint8_t bufSize, uint8_t amount, uint8_t addr);


// ====== УПАКОВЩИК GBUS ====== 
// запаковать данные для отправки (буфер, его размер, дата, адрес получателя, адрес отправителя)
// вернёт количество упакованных байт
// запакует согласно протоколу [суммарное количество байт, адрес получателя, адрес отправителя, ...байты даты..., CRC]
template <typename T> uint8_t packGBUSdata(uint8_t* buffer, uint8_t bufSize, T &data, uint8_t to, uint8_t from);

// распаковать данные, минуя служебные байты (буфер, его размер, дата)
// при успехе вернёт true. Вернёт false, если буфер слишком мал для даты
template <typename T> bool unpackGBUSdata(uint8_t* buffer, uint8_t bufSize, T &data);

// запаковать команду в буфер (буфер, команда, кому, от кого)
// команды: запрос (0), ответ (1)
// запакует согласно протоколу [команда, адрес получателя, адрес отправителя, CRC]
uint8_t packGBUScmd(uint8_t* buffer, uint8_t cmd, uint8_t to, uint8_t from);


// ====== УПАКОВЩИК БАЙТОВ ====== 
// пакуем любой тип данных в байтовый буфер (буфер, дата)
template <typename T> void packDataBytes(uint8_t *buffer, T &data);

// распаковываем из байтового буфера обратно (буфер, дата)
template <typename T> void unpackDataBytes(uint8_t *buffer, T &data);


// ============= CRC =============
// обновить CRC байта (crc, байт)
void GBUS_crc_update(uint8_t &crc, uint8_t data);

// расчёт crc для буфера (буфер, количество байт для проверки)
uint8_t GBUS_crc_bytes(uint8_t *data, uint8_t size);

// ========================================= РЕАЛИЗАЦИЯ =========================================
// crc дефайн
#if (GBUS_CRC == 1)
#define GBUS_OFFSET 4
#else
#define GBUS_OFFSET 3
#endif

// константы
#define ACK_IDLE 0
#define ACK_WAIT 1
#define ACK_ERROR 2
#define ACK_ONLY 3
#define ACK_DATA 4
#define GBUS_BROADCAST 255

template <typename T>
uint8_t packGBUSdata(uint8_t* buffer, uint8_t bufSize, T &data, uint8_t to, uint8_t from) {
    buffer[0] = sizeof(T) + GBUS_OFFSET;      // размер пакета с учётом служебных
    if (buffer[0] > bufSize) return 0;        // если переполним буфер
    buffer[1] = to;                           // адрес приёмника
    buffer[2] = from;                        // адрес передатчика    
    const uint8_t *ptr = (const uint8_t*) &data;                                // указатель
    for (uint16_t i = 0; i < sizeof(T); i++) buffer[i + 3] = *ptr++;            // пакуем дату    
    if (GBUS_CRC) buffer[sizeof(T) + 3] = GBUS_crc_bytes(buffer, sizeof(T) + 3);// crc    
    return buffer[0];
}

template <typename T> 
bool unpackGBUSdata(uint8_t* buffer, uint8_t bufSize, T &data) {
    if (sizeof(T) + GBUS_OFFSET > bufSize) return false;    // если данные больше буфера (+ служебная инфа протокола)
    uint8_t *ptr = (uint8_t*) &data;    
    for (uint16_t i = 0; i < sizeof(T); i++) *ptr++ = buffer[i + 3];    // пишем
    return true;
}

template <typename T>
void packDataBytes(uint8_t *buffer, T &data) {
    uint8_t *ptr = (uint8_t*) &data;
    for (uint16_t i = 0; i < sizeof(T); i++) {
        buffer[i] = *ptr++;
    }
}

template <typename T>
void unpackDataBytes(uint8_t *buffer, T &data) {
    uint8_t *ptr = (uint8_t*) &data;
    for (uint16_t i = 0; i < sizeof(T); i++) {
        *ptr++ = buffer[i];
    }
}

#endif