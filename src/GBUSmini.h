#ifndef _GBUSmini_h
#define _GBUSmini_h
#include "GyverBus.h"

// ==================== СТАНДАРТНЫЕ НАСТРОЙКИ ======================
// могут быть изменены здесь, либо прямо в скетче при помощи дефайна ПЕРЕД ПОДКЛЮЧЕНИЕМ БИБЛИОТЕКИ
// дефайны в скетч соответственно GBUS_SPEED, GBUS_OFFSET_WRITE, GBUS_OFFSET_READ
#define GBUS_DEFAULT_SPEED	400		// скорость (baud)
#define GBUS_DEFAULT_WRITE	8		// коррекция задержки записи, мкс
#define GBUS_DEFAULT_READ	5		// коррекция задержки чтения, мкс
#define GBUSMINI_BUSY_TIMEOUT 50	// таймаут отправки после предыдущей активности на линии, мс

// ========== ЛЁГКИЕ ФУНКЦИИ ОТПРАВКИ И ЧТЕНИЯ GBUS ==========
// По одному проводу
// Все функции (кроме GBUS_is_busy) блокируют выполнение кода на время приёма/отправки

// Возвращает true, если линия занята. Таймаут GBUS_BUSY_TIMEOUT мс
bool GBUS_is_busy(uint8_t pin);

// Отправить сырые данные (пин, дата, размер)
// Формат посылки GBUS [суммарное количество байт, адрес получателя, адрес отправителя, ...байты даты..., CRC]
// Функция блокирующая на всё время отправки
// 640 байт (Arduino Nano), 88 байт ATtiny13 (microCore)
void GBUS_send_raw(uint8_t pin, uint8_t* data, uint8_t size);

// Отправить данные с CRC (пин, адрес получателя, адрес отправителя, дата, размер)
// Функция блокирующая на всё время отправки
// 740 байт (Arduino Nano), 160 байт ATtiny13 (microCore)
void GBUS_send(uint8_t pin, uint8_t to, uint8_t from, uint8_t* data, uint8_t size);

// Прочитать сырые данные (пин, дата, размер)
// Вызывать как можно чаще, чтобы не пропустить. Функция блокирующая на всё время приёма.
// Возвращает количество принятых байт при завершении приёма
// 520 байт (Arduino Nano), 220 байт ATtiny13 (microCore)
uint8_t GBUS_read_raw(uint8_t pin, uint8_t* buf, uint8_t size);

// Прочитать данные с CRC (пин, наш адрес, дата, размер)
// Вызывать как можно чаще, чтобы не пропустить. Функция блокирующая на всё время приёма
// Возвращает адрес отправителя при успешном завершении приёма. При ошибке возвращает 0
// 650 байт (Arduino Nano), 330 байт ATtiny13 (microCore)
uint8_t GBUS_read(uint8_t pin, uint8_t addr, uint8_t* buf, uint8_t size);

// Отправить запрос (пин, адрес получателя, адрес отправителя)
// Функция блокирующая на всё время отправки
// 640 байт (Arduino Nano), 150 байт ATtiny13 (microCore)
void GBUS_send_request(uint8_t pin, uint8_t to, uint8_t from);

// Принять запрос (пин, наш адрес)
// Вызывать как можно чаще, чтобы не пропустить. Функция блокирующая на всё время приёма
// Возвращает адрес отправителя при успешном завершении приёма. При ошибке возвращает 0
// 540 байт (Arduino Nano), 220 байт ATtiny13 (microCore)
uint8_t GBUS_read_request(uint8_t pin, uint8_t addr);

// Отправить подтверждение (пин, адрес получателя, адрес отправителя)
// Функция блокирующая на всё время отправки
void GBUS_send_ack(uint8_t pin, uint8_t to, uint8_t from);

// Принять подтверждение (пин, наш адрес)
// Вызывать как можно чаще, чтобы не пропустить. Функция блокирующая на всё время приёма
// Возвращает адрес отправителя при успешном завершении приёма. При ошибке возвращает 0
uint8_t GBUS_read_ack(uint8_t pin, uint8_t addr);

// Отправить запрос и ждать подтверждения приёма, т.е. пытаться достучаться
// (пин, адрес получателя, адрес отправителя, кол-во попыток, таймаут между попытками)
// возвращает 0 при таймауте, 1 при успехе (получили ack)
// см. примеры call response _ack
uint8_t GBUS_send_request_ack(uint8_t pin, uint8_t to, uint8_t from, uint8_t tries, int timeout);


// *******************************************************
// ********************** СЕРВИС *************************
// *******************************************************

#if !defined(GBUS_SPEED)
#define GBUS_SPEED GBUS_DEFAULT_SPEED
#endif
#if !defined(GBUS_OFFSET_WRITE)
#define GBUS_OFFSET_WRITE GBUS_DEFAULT_WRITE
#endif
#if !defined(GBUS_OFFSET_READ)
#define GBUS_OFFSET_READ GBUS_DEFAULT_READ
#endif

#define GBUS_BIT    (1000000UL / GBUS_SPEED)
#define GBUS_BIT_2  (GBUS_BIT >> 1)

#endif