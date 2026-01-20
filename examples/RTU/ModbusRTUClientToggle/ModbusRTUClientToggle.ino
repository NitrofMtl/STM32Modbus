/*
  Modbus RTU Client Toggle

  This sketch toggles the coil of a Modbus RTU server connected via RS485
  on and off every second.

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server
     - Y connected to A/Y of the Modbus RTU server
     - Z connected to B/Z of the Modbus RTU server
     - Jumper positions
       - FULL set to OFF
       - Z \/\/ Y set to ON

  created 16 July 2018
  by Sandeep Mistry
*/

#include <STM32RS485DMA.h> // STM32Modbus depends on the STM32RS485DMA library
#include <STM32Modbus.h>

void setup() {
  Serial.begin(9600);

  Serial.println("Modbus RTU Client Toggle");

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
}

void loop() {
  // for (slave) id 1: write the value of 0x01, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x01)) {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

  // wait for 1 second
  delay(1000);

  // for (slave) id 1: write the value of 0x00, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x00)) {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

  // wait for 1 second
  delay(1000);
}
