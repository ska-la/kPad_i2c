//--- Simple example: input a symbol from keypad and push ones ---
//--- into a Serial interface. Prerequisites: arduino board and ---
//--- keypad 4x4(4x3 and so on..) without i2c interface ---

//--- ATTENTION: Don't forget to comment out the line ---
//--- #define _WIRE_H_ --- in kPad_i2c.h file ---
//--- ---

#include "kPad_i2c.h"

//--- define keypad matrix size ---
#define PAD_ROWS      4
#define PAD_COLS      4

//--- define keypad's chars table ---
char symbolChart[PAD_ROWS][PAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//--- define DIGITAL pins of Arduino board, which used by keypad ---
byte padPinIn[] = {2,3,4,5};
byte padPinOut[] = {6,7,8,9};

//--- Constructor invocation ---
kPad kp = kPad((char *)symbolChart,padPinIn,padPinOut,(byte)PAD_ROWS,(byte)PAD_COLS);

void setup() {
  Serial.begin(115200);
  kp.init();
//--- use only you aren't satisfied default delay ---
//kp.setDelay(100);
}

void loop() {
  char smbl = kp.read();
  if (smbl) {
    Serial.write(smbl);
  }
}
