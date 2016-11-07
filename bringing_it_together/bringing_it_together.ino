//expansion board dependencies
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>
#define TM1638_STB 5
#define TM1638_CLK 6
#define TM1638_DIO 7

TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);

//oled board requirements
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <SPI.h>
#include <Wire.h>

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 12
#define OLED_RESET 10

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

byte buttons;
static unsigned long thisMicros = 0;
static unsigned long lastMicros = 0;


void setup() {

  //setting up the display variables

  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}


void loop() {

  //variable for storing buttons pressed
  buttons = module.getButtons();

  if (buttons == 1) {
    for (int a = 0; a < 10000; a++)
    {
      module.setDisplayToDecNumber(a, 4, false);
      //first number is the value, second is the decimal poin1 is the right most decimal, true = show 0's before the number
      delay(1);
    }
  }

  if (buttons == 2) {
    for (int a = 0; a <= 255; a++)
    {
      module.setDisplayToDecNumber(a, 0, false);
      //first number is the value, second is the decimal poin1 is the right most decimal, true = show 0's before the actual int

      module.setLEDs(a);
      delay(1000);
    }
  }

  if (buttons == 4) {
    module.setDisplayToDecNumber(69, 4, true);
  }

  if (buttons == 8) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Welcome Nikola, the last time you pressed the button was: \n");
    display.print(thisMicros - lastMicros);
    display.print(" microseconds ago");
    display.display();
    lastMicros = thisMicros;
    thisMicros = micros();

    //to make sure people don't double tap the button and over write the data...
    delay(1000);
  }

  if (buttons == 16) {
    display.clearDisplay();
    display.drawCircle(32, 32, 16, WHITE);
    display.drawLine(32, 32, 32, 16, WHITE);
    display.drawLine(32, 32, 40, 32, WHITE);
    display.display();
  }

  if (buttons == 0) {
    module.clearDisplay();
  }


  //debugging the button pressed
  String debugText = "value is : ";
  String test = debugText + buttons;
  Serial.begin(9600);
  Serial.println(test);
}


