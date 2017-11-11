#include <Adafruit_SSD1306.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <SPI.h>
#include <Wire.h>



// If using hardware SPI :
#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 12
#define OLED_RESET 10


Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


void setup() {
  
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  Serial.begin(9600);
  Serial.print("[*] Finished Initialising Script! \n"); 
}
void loop()
{
  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;

  if (Serial.available() > 0) {
    String cmdString = Serial.readString();

    if (cmdString == "boop") {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Now is the time for all good men to come to the aid the party \n");
      display.print(thisMicros - lastMicros);
      display.print(" microseconds");
      display.display();
      lastMicros = thisMicros;
      thisMicros = micros();

    }
    else {
      display.clearDisplay();
      display.drawCircle(32, 32, 16, WHITE);
      display.drawLine(32, 32, 32, 16, WHITE);
      display.drawLine(32, 32, 40, 32, WHITE);
      display.display();
    }
  }
}
