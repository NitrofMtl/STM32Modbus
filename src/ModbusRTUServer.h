/*
  This file is part of the ArduinoModbus library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This fork:
    Copyright (c) 2026 NitrofMtl
    https://github.com/NitrofMtl/STM32Modbus

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
*/

#ifndef _MODBUS_RTU_SERVER_H_INCLUDED
#define _MODBUS_RTU_SERVER_H_INCLUDED

#include "ModbusServer.h"

//#ifdef USING_STM32RS485DMA
#include <STM32RS485DMA.h>
//#define RS485_CLASS RS485DMAClass
//#else
//#define RS485_CLASS RS485Class
//#include <ArduinoRS485.h>
//#endif

class ModbusRTUServerClass : public ModbusServer {
public:
  ModbusRTUServerClass();
  ModbusRTUServerClass(RS485_CLASS& rs485);
  virtual ~ModbusRTUServerClass();

  /**
   * Start the Modbus RTU server with the specified parameters
   *
   * @param id (slave) id of the server
   * @param baudrate Baud rate to use
   * @param config serial config. to use defaults to SERIAL_8N1
   *
   * Return 1 on success, 0 on failure
   */
  int begin(int id, unsigned long baudrate, uint16_t config = SERIAL_8N1);
  int begin(RS485_CLASS& rs485, int id, unsigned long baudrate, uint16_t config = SERIAL_8N1);

  /**
   * Poll interface for requests
   */
  virtual int poll();

private:
  RS485_CLASS* _rs485 = &RS485;
};

extern ModbusRTUServerClass ModbusRTUServer;

#endif
