# Upstream notes

Forked from ArduinoModbus v1.0.9

Core changes:
- Replaced ArduinoRS485 backend with STM32RS485DMA
- macro for rs485 object selection
- remove macro inclusion on config.h (compile error)
- remove call ```while (!Serial);````from all examples to allow Modbus to run without a physical Serial monitor connection

All Modbus protocol logic unchanged.
