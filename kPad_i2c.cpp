/*
Copyright 2014 Konstantin A. Suchkov

 kPad_i2c.cpp - part of a simple keypad library
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

#include "kPad_i2c.h"

#ifdef _WIRE_H_
kPad::kPad(char *kC,byte pr,byte pc) {
  _keysChart = kC;
  _pad_cols = pc;
  _pad_rows = pr;
  _i2c_addr = 0;
  _mDelay = 250;
};
#else
kPad::kPad(char *kC,byte *pia,byte *poa,byte pr,byte pc) {
  _keysChart = kC;
  _padPinIn = pia;
  _padPinOut = poa;
  _pad_cols = pc;
  _pad_rows = pr;
  _mDelay = 250;
};
#endif

#ifdef _WIRE_H_
void kPad::init(byte a) {
  _i2c_addr = a;
  Wire.begin(a);
  reset();
};
#else
void kPad::init(void) {
  for (byte m=0; m < _pad_rows; m++) {
    pinMode(_padPinIn[m],OUTPUT);
  }
  for (byte m=0; m < _pad_cols; m++) {
    pinMode(_padPinOut[m],INPUT_PULLUP);
  }
  reset();
};
#endif 

void kPad::reset(void) {
#ifdef _WIRE_H_
  Wire.beginTransmission(_i2c_addr);
  Wire.write(BOARD_MASK);
  Wire.endTransmission();
  delayMicroseconds(5);
#else
  for (byte c=0; c < _pad_rows; c++) {
    digitalWrite(_padPinIn[c],HIGH);
  }
  delay(1);
#endif
};

void kPad::setDelay(unsigned int da) {
  _mDelay = da;
}

#ifdef _WIRE_H_
char kPad::read(void) {
  if ( millis() - _sDelay < _mDelay ) return 0;	//--- ignore read wile delay ---
  _res = ' ';
  reset();
  for (byte a=1,c=0; a <= 0x08; a=a<<1,c++) {
    Wire.beginTransmission(_i2c_addr);
    Wire.write( a^BOARD_MASK );
    Wire.endTransmission();
    delayMicroseconds(5);
    Wire.requestFrom((int)_i2c_addr,1,true);
    byte b=0;
    b = (BOARD_MASK ^ Wire.read()) >> 4;
    if ( b != 0 ) {
      if ( b == 1) b = 0;
      if ( b == 2) b = 1;
      if ( b == 4) b = 2;
      if ( b == 8 ) b = 3;
//      Serial.print(_keysChart[c*_pad_rows+b]);  for debug purpose
      _res = _keysChart[c*_pad_rows+b];
      _sDelay = millis();
      return _res;
    }
  }
  return 0;
};
#else
char kPad::read(void) {
  if ( millis() - _sDelay < _mDelay ) return 0;	//--- ignore read wile delay ---
  _res = ' ';
  reset();
  for (byte a=0; a < _pad_rows; a++) {
    digitalWrite(_padPinIn[a],LOW);
    delayMicroseconds(1);
    for (byte b=0; b < _pad_cols; b++) {
      if (digitalRead(_padPinOut[b]) == LOW) {
        _res =  _keysChart[a*_pad_rows+b];
        break;
      }
    }
    digitalWrite(_padPinIn[a],HIGH);
    if (_res != ' ') {
	_sDelay = millis();
	return _res;
    }
  }
  return 0;
};
#endif
