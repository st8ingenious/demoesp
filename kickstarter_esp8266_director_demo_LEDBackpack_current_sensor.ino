#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
 
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment led = Adafruit_7segment();
int wait=0;
int tt;
void setup() {
  Serial.begin(9600);
  led.begin(0x70);
   
  emon1.current(0,9); 
    delay(500);
}

void loop() {
double Irms = emon1.calcIrms(1480);  // Calculate Irms only
 int watt=Irms*230-10;            //offset -10w
 if (watt<0){
watt=0;  
 }
  Serial.println(watt);         // Apparent power
  
   led.println(watt);
    led.writeDisplay();
    //delay(500);


}
