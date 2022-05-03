[![Foo](https://img.shields.io/badge/Version-2.5-brightgreen.svg?style=flat-square)](#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)

[![Foo](https://img.shields.io/badge/README-ENGLISH-brightgreen.svg?style=for-the-badge)](https://github-com.translate.goog/GyverLibs/GyverBus?_x_tr_sl=ru&_x_tr_tl=en)

# GyverBus
Библиотека для общения по протоколу GBUS
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

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

### Документация
К библиотеке есть [расширенная документация](https://alexgyver.ru/GyverBus/)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverBus** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverBus/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
См. [документацию](https://alexgyver.ru/GyverBus/)

<a id="usage"></a>
## Использование
См. [документацию](https://alexgyver.ru/GyverBus/)

<a id="example"></a>
## Пример
См. [документацию](https://alexgyver.ru/GyverBus/)

<a id="versions"></a>
## Версии
- v1.1: добавлена waitAck() и исправлена ошибочка
- v1.2: улучшена стабильность, функции оптимизированы, уменьшен вес
- v1.3: добавлен CRC в запрос и ответ
- v2.0: 
    - Куча оптимизации
    - Логика работы переделана. Теперь GBUS работает для всех uart-библиотек
    - Однопроводной uart вынесен отдельным классом
    - Добавлена совместимость с esp8266
    - Переделана вся инициализация, смотри примеры!
    - Добавлены утилиты и примеры
- v2.1: вернул getStatus
- v2.2: небольшие багфиксы и оптимизация
- v2.3: добавлена возможность отправки широковещательного сообщения (всем), отправлять на адрес 255
- v2.4: исправлены ошибки, добавлена bool statusChanged() для GBUS
- v2.5: добавил пример с GyverTransfer, добавил смену адреса

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!
