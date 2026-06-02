This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverBus.svg?color=brightgreen)](https://github.com/GyverLibs/GyverBus/releases/latest/download/GyverBus.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverBus.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverBus)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverBus?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverBus
Library for communication using the GBUS protocol
- Very simple, reliable, resistant to interference and delay, but slow communication interface based on UART
- Two-way communication on one wire
- Asynchronous sending and reading (based on millis())
- Two-way compatibility with hardware UART
- Ability to receive and send data within the Arduin network
- Addressing up to 254 devices on the network (1 to 255)
- omnivorous sending and receiving function (eating variables, structures, arrays)
- Built-in CRC (integrity control) check of a data packet
- Ability to send and read a short “request”
- All Arduino-compatible boards are supported
- The library itself provides debugging capabilities (error codes)
- In the examples there are compact options for reading and sending data, even fits into ATtiny.

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

### Documentation.
There's a library[extended documentation](https://alexgyver.ru/GyverBus/)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverBus** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverBus/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
See.[documentation](https://alexgyver.ru/GyverBus/)

<a id="usage"></a>
## Use of use
See.[documentation](https://alexgyver.ru/GyverBus/)

<a id="example"></a>
## Example
See.[documentation](https://alexgyver.ru/GyverBus/)

<a id="versions"></a>
## Versions
- v1.1: Added waitAck() and corrected error
- v1.2: improved stability, functions optimized, reduced weight
- v1.3: CRC added to request and response
- v2.0: 
    - Plenty of optimization
    - The logic of the work has been reworked. GBUS now works for all uart libraries
    - Single-wire uart made a separate class
    - Compatibility with esp8266
    - All initializations have been redesigned, see examples!
    - Added utility and examples
- v2.1: GetStatus returned
- v2.2: small bugfixes and optimization
- v2.3: Added the ability to send a broadcast message (to all), to 255
- v2.4: Fixed errors, added bool statusChanged() for GBUS
- v2.5: added an example from GyverTransfer, added a change of address
- v2.6: small fixtures

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
