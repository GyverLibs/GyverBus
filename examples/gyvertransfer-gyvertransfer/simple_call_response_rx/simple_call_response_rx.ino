// принимаем запрос и отправляем в ответ данные с АЦП

#define GT_STREAM_MODE  // STREAM_MODE нужен для работы GBUS
#include <GyverTransfer.h>
GyverTransfer<2, GT_TRX> trans;

#include "GBUS.h"
GBUS bus(&trans, 3, 20);  // адрес 3, буфер 20 байт

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

  // приняли данные
  if (bus.gotRequest()) {
    Serial.print("request from: ");
    Serial.println(bus.getTXaddress());

    // ответили
    //bus.sendAck(bus.getTXaddress());

    // ИЛИ отправили дату (случайный байт) в ответ
    byte data = random(255);
    Serial.print("sending: ");
    Serial.println(data);
    bus.sendData(bus.getTXaddress(), data);
  }
}
