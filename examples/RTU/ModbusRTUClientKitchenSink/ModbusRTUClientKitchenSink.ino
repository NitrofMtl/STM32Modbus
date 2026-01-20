#include <Arduino.h>
//#include "Timeout.h"
//#include "ArduinoModbus.h"
//#include "STM32Modbus.h"


const uint32_t modbusBaud = 9600;
const uint32_t modbusBaudPostDelay = 1000000 / modbusBaud * 12 * 2.5; 

//#define KITCHENSINKCLIENTEX
//#define KITCHENSINKCERVEX
//#define COILSERVEX
//#define TEST_READ_FRAME
#define TEST_EXAMPLES

#ifdef KITCHENSINKCLIENTEX

int counter = 0;

void writeCoilValues();
void readCoilValues();
void readDiscreteInputValues();
void writeHoldingRegisterValues();
void readHoldingRegisterValues();
void readInputRegisterValues(); 

Interval monitor;
void monClb()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  
  writeCoilValues();

  readCoilValues();

  readDiscreteInputValues();

  writeHoldingRegisterValues();

  readHoldingRegisterValues();

  readInputRegisterValues();

  counter++;
}




void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  monitor.interval(1000, monClb);

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(modbusBaud)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
  RS485.setDelays(50, modbusBaudPostDelay);
}

void loop() {
  TimeOut::handler();
/*  if (RS485.available()) {
    Serial.print(RS485.read());
  }*/
}
  

void writeCoilValues() {
  // set the coils to 1 when counter is odd
  byte coilValue = ((counter % 2) == 0) ? 0x00 : 0x01;

  Serial.print("Writing Coil values ... ");

  // write 10 Coil values to (slave) id 42, address 0x00
  ModbusRTUClient.beginTransmission(42, COILS, 0x00, 10);
  for (int i = 0; i < 10; i++) {
    ModbusRTUClient.write(coilValue);
  }
  if (!ModbusRTUClient.endTransmission()) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
  }

  // Alternatively, to write a single Coil value use:
  // ModbusRTUClient.coilWrite(...)
}

void readCoilValues() {
  Serial.print("Reading Coil values ... ");

  // read 10 Coil values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, COILS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Coil value use:
  // ModbusRTUClient.coilRead(...)
}

void readDiscreteInputValues() {
  Serial.print("Reading Discrete Input values ... ");

  // read 10 Discrete Input values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, DISCRETE_INPUTS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Discrete Input value use:
  // ModbusRTUClient.discreteInputRead(...)
}

void writeHoldingRegisterValues() {
  // set the Holding Register values to counter

  Serial.print("Writing Holding Registers values ... ");

  // write 10 coil values to (slave) id 42, address 0x00
  ModbusRTUClient.beginTransmission(42, HOLDING_REGISTERS, 0x00, 10);
  for (int i = 0; i < 10; i++) {
    ModbusRTUClient.write(counter);
  }
  if (!ModbusRTUClient.endTransmission()) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
  }

  // Alternatively, to write a single Holding Register value use:
  // ModbusRTUClient.holdingRegisterWrite(...)
}

void readHoldingRegisterValues() {
  Serial.print("Reading Input Register values ... ");

  // read 10 Input Register values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, HOLDING_REGISTERS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Holding Register value use:
  // ModbusRTUClient.holdingRegisterRead(...)
}

void readInputRegisterValues() {
  Serial.print("Reading input register values ... ");

  // read 10 discrete input values from (slave) id 42,
  if (!ModbusRTUClient.requestFrom(42, INPUT_REGISTERS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Input Register value use:
  // ModbusRTUClient.inputRegisterRead(...)
}
#endif


#ifdef KITCHENSINKCERVEX

const int numCoils = 10;
const int numDiscreteInputs = 10;
const int numHoldingRegisters = 10;
const int numInputRegisters = 10;

void printFrame()
{
  uint8_t buf[50] = {};
  size_t len = 0;//85.available();
  //RS485.readBytes(buf, len);
  //if (len == 0) return;
  Serial.print("Frame: ");
  //Serial.println(len);
  /*for ( uint8_t i = 0; i < len; i++ ) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
  }*/
}

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  //RS485 = RS485Class(Serial2, 16, 23, -1);
  //RS485.setDelays(50, modbusBaudPostDelay);
  RS485.setDelays(50, RS485.getUsecForNChar(3.5)); // 12 chars time at current baudrate

  //delay(1000);

  Serial.println("Modbus RTU Server Kitchen Sink");

  // start the Modbus RTU server, with (slave) id 42
  if (!ModbusRTUServer.begin(42, modbusBaud)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  //delay(1000);

  // configure coils at address 0x00
  ModbusRTUServer.configureCoils(0x00, numCoils);

  // configure discrete inputs at address 0x00
  ModbusRTUServer.configureDiscreteInputs(0x00, numDiscreteInputs);

  // configure holding registers at address 0x00
  ModbusRTUServer.configureHoldingRegisters(0x00, numHoldingRegisters);

  // configure input registers at address 0x00
  ModbusRTUServer.configureInputRegisters(0x00, numInputRegisters);

  Serial.println("Setup complete");
}

void loop() {
  // poll for Modbus RTU requests
  ModbusRTUServer.poll();
  //void printFrame();

  // map the coil values to the discrete input values
  for (int i = 0; i < numCoils; i++) {
    int coilValue = ModbusRTUServer.coilRead(i);

    ModbusRTUServer.discreteInputWrite(i, coilValue);
  }

  // map the holding register values to the input register values
  for (int i = 0; i < numHoldingRegisters; i++) {
    long holdingRegisterValue = ModbusRTUServer.holdingRegisterRead(i);

    ModbusRTUServer.inputRegisterWrite(i, holdingRegisterValue);
  }
}
#endif




#ifdef COILSERVEX

const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(9600);

  Serial.println("Modbus RTU Server LED");

  RS485.setDelays(50, modbusBaudPostDelay);

  // start the Modbus RTU server, with (slave) id 1
  if (!ModbusRTUServer.begin(1, modbusBaud)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // configure a single coil at address 0x00
  ModbusRTUServer.configureCoils(0x00, 1);
}

void loop() {
  // poll for Modbus RTU requests
  int packetReceived = ModbusRTUServer.poll();

  if(packetReceived) {
    // read the current value of the coil
    int coilValue = ModbusRTUServer.coilRead(0x00);
  
    if (coilValue) {
      // coil value set, turn LED on
      digitalWrite(ledPin, HIGH);
    } else {
      // coil value clear, turn LED off
      digitalWrite(ledPin, LOW);
    }
  }
}

#endif

/*
I think I want to break down thing to be certain to respect logic and also not breaking arduino read() logic: 
first, set the working conditions: 
  a frame star when rx start, 
  stop when idle, 
  is aprove when idle delay is pass. then frame is consume then reset. 
  
between start and approved, 2 case could append: 
  1 idle is detected but restart before delay is over-> 
    the frame should continue; 
    other case: the delay is passed, but new data is comming-> the new data must be invalidated...



    Document it as:

“Transport-level framing for deterministic embedded systems”
*/ 




#ifdef TEST_READ_FRAME

/*void printFrame()
{
  uint8_t buf[50] = {};
  size_t len = RS485.readBytes(buf, 50);
  while(len!=0){
    
    Serial.println();
    Serial.print("[Frame: ");
    Serial.print(len);
    Serial.println("]");
    for ( uint8_t i = 0; i < len; i++ ) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
    }
    len = RS485.readBytes(buf, len);
  }
}*/

/*void printFrame()
{
  uint8_t buf[50] = {};
  size_t len = RS485.readBytes(buf, 2);
  if (len==0) return;
  Serial.println();
  Serial.print("[Frame: ");
  Serial.print(len);
  Serial.println("]");
  Serial.print(buf[0], HEX);
  Serial.print(" ");
  Serial.print(buf[1], HEX);
  Serial.println();
  while(len!=0){
    
    
    for ( uint8_t i = 0; i < len; i++ ) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
    }
    len = RS485.readBytes(buf, len);
  }
}*/

void printFrame()
{
  uint8_t buf[50] = {};
  size_t len = RS485.readBytes(buf, 50);
  if (len==0) return;
  Serial.println();
  Serial.print("[Frame: ");
  Serial.print(len);
  Serial.println("]");
  //Serial.print(buf[0], HEX);
  //Serial.print(" ");
  //Serial.print(buf[1], HEX);
  //Serial.println();
  //while(len!=0){
    
    
    for ( uint8_t i = 0; i < len; i++ ) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
    }
    //len = RS485.readBytes(buf, len);
  //}
}


void setup() {
  Serial.begin(9600);
  while (!Serial);

  delay(2000);

  RS485.setDelays(50, modbusBaudPostDelay);
  RS485.begin(modbusBaud);

  Serial.println("Setup Over");
}

void loop()
{
  /*Serial.println("Waiting for data...");
  delay(1000);
  if (RS485.available()) {
    Serial.print("Data available: ");
    Serial.println(RS485.available());
  } */
  printFrame();
  /*if (RS485.available()) {
    Serial.print(RS485.read(), HEX);
    Serial.print(" ");
  }*/
 //Serial.println("running");
 //delay(1000);
}

#endif

#ifdef TEST_EXAMPLES


/*
  Modbus RTU Client Kitchen Sink

  This sketch creates a Modbus RTU Client and demonstrates
  how to use various Modbus Client APIs.

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server
     - Y connected to A/Y of the Modbus RTU server
     - Z connected to B/Z of the Modbus RTU server
     - Jumper positions
       - FULL set to OFF
       - Z \/\/ Y set to ON

  created 18 July 2018
  by Sandeep Mistry
*/

#include <STM32RS485DMA.h> // STM32Modbus depends on the STM32RS485DMA library
#include <STM32Modbus.h>

int counter = 0;

void writeCoilValues();

void readCoilValues();

void readDiscreteInputValues();

void writeHoldingRegisterValues();

void readHoldingRegisterValues();

void readInputRegisterValues();

void setup() {
  Serial.begin(9600);

  Serial.println("Modbus RTU Client Kitchen Sink");

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
}

void loop() {
  writeCoilValues();

  readCoilValues();

  readDiscreteInputValues();

  writeHoldingRegisterValues();

  readHoldingRegisterValues();

  readInputRegisterValues();

  counter++;

  delay(5000);
  Serial.println();
}

void writeCoilValues() {
  // set the coils to 1 when counter is odd
  byte coilValue = ((counter % 2) == 0) ? 0x00 : 0x01;

  Serial.print("Writing Coil values ... ");

  // write 10 Coil values to (slave) id 42, address 0x00
  ModbusRTUClient.beginTransmission(42, COILS, 0x00, 10);
  for (int i = 0; i < 10; i++) {
    ModbusRTUClient.write(coilValue);
  }
  if (!ModbusRTUClient.endTransmission()) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
  }

  // Alternatively, to write a single Coil value use:
  // ModbusRTUClient.coilWrite(...)
}

void readCoilValues() {
  Serial.print("Reading Coil values ... ");

  // read 10 Coil values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, COILS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Coil value use:
  // ModbusRTUClient.coilRead(...)
}

void readDiscreteInputValues() {
  Serial.print("Reading Discrete Input values ... ");

  // read 10 Discrete Input values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, DISCRETE_INPUTS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Discrete Input value use:
  // ModbusRTUClient.discreteInputRead(...)
}

void writeHoldingRegisterValues() {
  // set the Holding Register values to counter

  Serial.print("Writing Holding Registers values ... ");

  // write 10 coil values to (slave) id 42, address 0x00
  ModbusRTUClient.beginTransmission(42, HOLDING_REGISTERS, 0x00, 10);
  for (int i = 0; i < 10; i++) {
    ModbusRTUClient.write(counter);
  }
  if (!ModbusRTUClient.endTransmission()) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
  }

  // Alternatively, to write a single Holding Register value use:
  // ModbusRTUClient.holdingRegisterWrite(...)
}

void readHoldingRegisterValues() {
  Serial.print("Reading Input Register values ... ");

  // read 10 Input Register values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(42, HOLDING_REGISTERS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Holding Register value use:
  // ModbusRTUClient.holdingRegisterRead(...)
}

void readInputRegisterValues() {
  Serial.print("Reading input register values ... ");

  // read 10 discrete input values from (slave) id 42,
  if (!ModbusRTUClient.requestFrom(42, INPUT_REGISTERS, 0x00, 10)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

  // Alternatively, to read a single Input Register value use:
  // ModbusRTUClient.inputRegisterRead(...)
}

#endif