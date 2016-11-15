#include <Interrupt.h>
#include <TimerListener.h>
#include <RifIntEncoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// ------------------------------------------------------------------------------------
//
// configuration
//
// ------------------------------------------------------------------------------------
 // -- OLED display ------------------------------------------------------------------

// OLED screen via hardware SPI :
#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 12 // not used - manually wired to GND - active low - only one device on SPI bus
// but dont want SSD1396/SPI code interfering with any other pin so
//set to 12 which is actually MISO pin of SPI hardware bus, but not currently used
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
 // -- encoder config ----------------------------------------------------------------
#define THROTTLE_ENCODERA_PIN 2
#define THROTTLE_ENCODERB_PIN 3
#define THROTTLEMIN 0
#define THROTTLEMAX 180
RifIntEncoder knob;
// ------------------------------------------------------------------------------------
void setup() { // put your setup code here, to run once:
// ------------------------------------------------------------------------------------
 display.begin(SSD1306_SWITCHCAPVCC);
 display.display();
 delay(1000);

 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 // -- initialise interrupt handler sub-system ----------------
 Interrupt::initialiseStaticISRVectorTable() ;
 // -- encoders ------------------------------------------------
 knob.init(THROTTLE_ENCODERA_PIN, THROTTLE_ENCODERB_PIN);
 knob.setMax(THROTTLEMAX);
 knob.setMin(THROTTLEMIN);

} // setup
// ------------------------------------------------------------------------------------
//
void loop() { // put your main code here, to run repeatedly:
//
//
// ------------------------------------------------------------------------------------
 display.clearDisplay();
 display.setCursor(0,0);


 display.print(knob.getPos());
 display.display();

}
