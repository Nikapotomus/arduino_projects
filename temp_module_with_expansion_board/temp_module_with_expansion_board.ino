#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>
#define TM1638_STB 5
#define TM1638_CLK 6
#define TM1638_DIO 7

int sensorPin = 0;

TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);

unsigned long a = 1;

byte buttons;

void setup() {
  
  Serial.begin(9600);
  
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
  
  if (buttons == 128) {
    module.clearDisplay();
    module.setLEDs(0);
  }

 
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin); 
  
  // converting that reading to voltage, for 3.3v arduino use 3.3
  
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  
  // print out the voltage
  //     Serial.print(voltage); Serial.println(" volts");
  
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((volatge - 500mV) times 100)
//  Serial.print(temperatureC); Serial.println(" degrees C");

  char text[4];
  
  
  module.setDisplayToDecNumber(temperatureC * 10, 2, false);

  if (temperatureC < 16 | temperatureC > 30){
    sprintf(text, "HR");
    module.setLEDs(255);  
  }
  else if (temperatureC < 18 | temperatureC > 25){
    sprintf(text, "BAD");
    module.setLEDs(15);  
  }
  else if (temperatureC < 20 | temperatureC > 23){
    sprintf(text, "NICE");
    module.setLEDs(1);  
  }

  module.setDisplayToString(text); 
  
  delay(10000); 
  
  //     // now convert to Fahrenheight
  //     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  //     Serial.print(temperatureF); Serial.println(" degrees F");
 
//  Serial.println(test);
}


