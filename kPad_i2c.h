/*
Copyright 2014 Konstantin A. Suchkov

 kPad_i2c.h - part of a simple keypad library
              with TWI/I2C interface (IC PCF8574) for Arduino

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

 mail to: akdotvokchusatgmaildotcom
*/

//------------- comment out a statement below if you won't use ---
//------------- a keypad through i2c interface -----------------------
#define _WIRE_H_

#ifndef kPad_h
#define kPad_h

#include <Arduino.h>

#ifdef _WIRE_H_
#include <Wire.h>
#define BOARD_MASK 0xF7   //-- change to 0xFF if you'll use IC PCF8574 --
                          //-- outside a TWI/I2C interface board (alone) --
#endif 

class kPad {
  public:
#ifdef _WIRE_H_
    kPad(char*,byte,byte);
    void init(byte);
#else
    kPad(char*,byte*,byte*,byte,byte);
    void init(void);
#endif 
    char read(void);
    void setDelay(unsigned int);

  private:
#ifdef _WIRE_H_
    byte _i2c_addr;
#endif 
    byte _pad_cols;
    byte _pad_rows;
    char *_keysChart;
#ifndef _WIRE_H_
    byte* _padPinIn;
    byte* _padPinOut;
#endif 
    void reset(void);
    char _res;
    unsigned long _sDelay;	//--- start of delay ---
    unsigned int _mDelay;	//--- magnitude of delay ---
};

#endif 

