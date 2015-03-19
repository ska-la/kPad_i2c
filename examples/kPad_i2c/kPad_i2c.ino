//--- made by SKA ---
//--- keypad 4x4 (4x3 and so on..) with I2C interface -----
//--- symple input from keypad and relay to serial port ---

#include <Wire.h>
#include "kPad_i2c.h"

#define KPAD_I2C_ADDR 0x25	//--- change to your address ---

#define PAD_ROWS      4
#define PAD_COLS      4

char symbolChart[PAD_ROWS][PAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

kPad kp = kPad((char *)symbolChart,(byte)PAD_ROWS,(byte)PAD_COLS);

void setup() {
  Serial.begin(115200);
  kp.init(KPAD_I2C_ADDR);
//--- use only you aren't satisfied default delay ---
//kp.setDelay(100);
}

void loop() {
  char smbl = kp.read();
  if (smbl) {
    Serial.write(smbl);
  }
}
