This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverbus
Library for communication on the GBUS protocol
- very simple, reliable, resistant to interference and delays, but a slow communication interface based on UART
- bilateral communication one wire
- asynchronous sending and reading (based on Millis ())
- double -sided compatibility with hardware UART
- the ability to accept and send data inside the arduni network
- Addressing up to 254 devices on the network (from 1 to 255)
- omnivorous function of sending and reception (eats variables, structures, arrays)
- Built -in CRC check (integrity control) data package
- The possibility of sending and reading a short "request"
- all Arduino-compatible boards are supported
- The library itself provides debugging opportunities (error codes)
- In the examples there are compact options for reading and sending data, it will even fit into Attiny

## compatibility
Compatible with all arduino platforms (used arduino functions)

### Documentation
There is [extended documentation] to the library (https://alexgyver.ru/gyverbus/)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverbus ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverbus/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
See [documentation] (https://alexgyver.ru/gyverbus/)

<a id="usage"> </a>
## Usage
See [documentation] (https://alexgyver.ru/gyverbus/)

<a id="EXAMPLE"> </a>
## Example
See [documentation] (https://alexgyver.ru/gyverbus/)

<a id="versions"> </a>
## versions
- v1.1: added Waitack () and a mistake is fixed
- V1.2: Improved stability, the functions are optimized, the weight is reduced
- V1.3: Added CRC to the request and answer
- V2.0:
    - A bunch of optimization
    - The logic of work has been converted.Now GBUS is working for all UART Bibliotek
    - one -wire UART is carried out by a separate class
    - Added compatibility with ESP8266
    - All initialization has been redone, see examples!- Added utilities and examples
- V2.1: Returned Getstatus
- V2.2: Small Bagfixes and Optimization
- V2.3: added the possibility of sending a broadcast message (to all), send to the address 255
- V2.4: Fixed errors, added Bool Statuschand () for GBUS
- V2.5: added an example with Gyvertransfer, added address change
- V2.6: Small fixes

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code