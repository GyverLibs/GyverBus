// отправляем запрос через GyverTransfer
#define GT_STREAM_MODE  // STREAM_MODE нужен для работы GBUS
#include <GyverTransfer.h>
GyverTransfer<2, GT_TRX> trans;

#include "GBUS.h"
GBUS bus(&trans, 5, 20);  // адрес 5, буфер 20 байт

void setup() {
  Serial.begin(9600);
}

void loop() {
  // отправляем на адрес 3
  Serial.print("request to: ");
  Serial.println(3);
  bus.sendRequest(3);
  delay(2000);

  // tick() тут не нужен! Он занимается только приёмом данных
  // отправка делается так, как реализовано в используемой либе интерфейса
}
