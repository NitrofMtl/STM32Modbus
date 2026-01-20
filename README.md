# STM32Modbus


STM32Modbus is a fork of ArduinoModbus adapted for STM32-based Arduino boards
using a DMA-based RS485 backend.

The public Modbus API is preserved. Existing ArduinoModbus sketches
can typically be reused without modification.



## Important differences from ArduinoModbus

This library is a fork of ArduinoModbus with a different RS485 backend.

- Uses **[STM32RS485DMA](https://github.com/NitrofMtl/STM32RS485DMA)** instead of ArduinoRS485
- Designed for **STM32 boards with DMA-capable UARTs**
- RX/TX are managed using **DMA and UART IDLE detection**
- RX and TX cannot run simultaneously (hardware/DMA constraint)
- Frame reception is DMA-driven (no RXNE-based byte interrupts)

These differences are internal. The Modbus API remains unchanged.

## Fork origin

This project is forked from ArduinoModbus **v1.0.9**.



## Dependency

This library requires:

- **[STM32RS485DMA](https://github.com/NitrofMtl/STM32RS485DMA)**

ArduinoRS485 is **not used** and should not be installed alongside this library.



## Usage

The API and usage are identical to ArduinoModbus.

Please refer to the ArduinoModbus documentation for detailed usage examples:

https://www.arduino.cc/reference/en/libraries/arduinomodbus/


All ModbusClient and ModbusServer examples apply.
Only the RS485 transport layer is different.


## Supported platforms

- STM32-based Arduino boards
- Tested on:
  - Arduino Opta

Other STM32 boards may work but require correct DMA/UART configuration.


## License

STM32Modbus is a fork of [ArduinoModbus](https://github.com/arduino-libraries/ArduinoModbus)  
Original library: Copyright (c) 2018-2025 Arduino  
This fork: Copyright (c) 2026 NitrofMtl  

STM32Modbus is licensed under the **GNU General Public License v2 or later (GPLv2+)**.  
This means you are free to use, modify, and distribute this library under the same license.

For the full license, see the [LICENSE](LICENSE) file included in this repository, or visit [GNU GPL](http://www.gnu.org/licenses/).




















// Define the repository information in these attributes
:repository-owner: arduino-libraries
:repository-name: ArduinoModbus

= Modbus Library for Arduino =

image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/check-arduino.yml/badge.svg["Check Arduino status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/check-arduino.yml"]
image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/compile-examples.yml/badge.svg["Compile Examples status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/compile-examples.yml"]
image:https://github.com/{repository-owner}/{repository-name}/actions/workflows/spell-check.yml/badge.svg["Spell Check status", link="https://github.com/{repository-owner}/{repository-name}/actions/workflows/spell-check.yml"]

Use http://www.modbus.org/[Modbus] with your Arduino. 

Using TCP or RS485 shields, like the MKR 485 Shield. This library depends on the ArduinoRS485 library.

This library is based on https://github.com/stephane/libmodbus[libmodbus], modifications were made to the lower level RS485 and TCP layers to use Arduino Serial/RS485 and Client API's. Then an Arduino friendly API was added on top.

For more information about this library please visit us at
https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus

== Useful resources ==

* https://en.wikipedia.org/wiki/Modbus[Modbus - Wikipedia]
* http://www.modbus.org/faq.php[Modbus FAQ]

== License ==

Copyright (c) 2018 Arduino SA. All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
