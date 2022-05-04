This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverBus
Library for communication via GBUS protocol
- Very simple, reliable, noise and latency resistant, but slow UART-based communication interface
- Two-way communication over one wire
- Asynchronous send and read (based on millis())
- Two-way compatible with hardware UART
- Ability to send and receive data within the Arduino network
- Addressing up to 254 devices on the network (from 1 to 255)
- Omnivorous send and receive function (eats variables, structures, arrays)
- Built-in CRC check (continuity check) of the data packet
- Ability to send and read a short "request"
- All Arduino-compatible boards are supported
- The library itself provides debugging capabilities (error codes)
- In the examples there are compact options for reading and sending data, it will even fit into ATtiny

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

### Documentation
The library has [extended documentation](https://alexgyver.ru/GyverBus/)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverBus** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/GyverBus/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
See [documentation](https://alexgyver.ru/GyverBus/)

<a id="usage"></a>
## Usage
See [documentation](https://alexgyver.ru/GyverBus/)

<a id="example"></a>
## Example
See [documentation](https://alexgyver.ru/GyverBus/)

<a id="versions"></a>
## Versions
- v1.1: added waitAck() and fixed bug
- v1.2: improved stability, optimized features, reduced weight
- v1.3: added CRC to request and response
- v2.0:
    - Tons of optimizations
    - The logic of work has been redone. Now GBUS works for all uart libraries
    - Single-wire uart is taken out as a separate class
    - Added compatibility with esp8266
    - All initialization has been redone, see examples!
    - Added utilities and examples
- v2.1: returned getStatus
- v2.2: small bug fixes and optimization
- v2.3: added ability to send broadcast message (to everyone), send to address 255
- v2.4: fixed bugs, added bool statusChanged() for GBUS
- v2.5: added GyverTransfer example, added address change

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!