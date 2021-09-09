// отправляем запрос с подтверждением

#define GT_STREAM_MODE  // STREAM_MODE нужен для работы GBUS
#include <GyverTransfer.h>
GyverTransfer<2, GT_TRX> trans;

#include "GBUS.h"
GBUS bus(&trans, 5, 20);  // адрес 5, буфер 20 байт

void setup() {
  Serial.begin(9600);
  // прерывания по CHANGE для приёма
  attachInterrupt(0, isr, CHANGE);
}

// GyverTransfer читает в прерывании
void isr() {
  trans.tickISR();
}

void loop() {
  // здесь принимаются данные
  // если это аппаратный сериал - слишком часто его опрашивать даже не нужно
  bus.tick();

  // отправляем запрос на адрес 3 каждые 5 секунд
  static uint32_t tmr;
  if (millis() - tmr > 5000) {
    tmr = millis();
    Serial.println("send request");
    bus.sendRequest(3);
  }

  // ждём ответа от 3
  // пытаемся достучаться через таймаут 500мс 3 раза
  byte state = bus.waitAck(3, 3, 500);
  switch (state) {
    case ACK_IDLE: //Serial.println("idle");
      break;
    case ACK_WAIT: //Serial.println("wait");
      break;
    case ACK_ERROR: Serial.println("ack error");
      break;
    case ACK_ONLY: Serial.println("got ack");
      break;
    case ACK_DATA: Serial.print("got data: ");
      // читаем и выводим
      byte val;
      bus.readData(val);
      Serial.println(val);
      break;
  }
}
