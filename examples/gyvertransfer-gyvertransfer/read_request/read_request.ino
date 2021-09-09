// принимаем запрос через GyverTransfer
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
  bus.tick();

  // приняли данные
  if (bus.gotRequest()) {
    Serial.print("request from: ");
    Serial.println(bus.getTXaddress());
  }
}
