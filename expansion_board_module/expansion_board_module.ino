#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>
#define TM1638_STB 5
#define TM1638_CLK 6
#define TM1638_DIO 7

TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);

unsigned long a = 1;

byte buttons;

void setup() {
  // set up a pattern on the LEDs

  //
  //module.setLED(TM1638_COLOR_RED, 7);  // set LED number x to red
  //module.setLED(TM1638_COLOR_GREEN, 5); // set LED number x to green
  //module.setLED(TM1638_COLOR_RED+TM1638_COLOR_GREEN, 3); // set LED number x to red and green
}
void loop() {
  buttons = module.getButtons();
  String debugText = "value is : ";

  String test = debugText + buttons;

  if (buttons == 1) {
    for (a = 0; a < 10000; a++)
    {
      module.setDisplayToDecNumber(a, 4, false);
      //first number is the value, second is the decimal poin1 is the right most decimal, true = show 0's before the number
      delay(1);
    }
  }

  if (buttons == 2) {
    for (a = 0; a <= 255; a++)
    {
      module.setDisplayToDecNumber(a, 0, false);
      //first number is the value, second is the decimal poin1 is the right most decimal, true = show 0's before the actual int

      module.setLEDs(a);
    }
  }

  if (buttons == 4) {
    module.setDisplayToDecNumber(69, 4, true);
  }

  if (buttons == 0) {
    module.clearDisplay();
  }

  Serial.begin(9600);
  Serial.println(test);


}


