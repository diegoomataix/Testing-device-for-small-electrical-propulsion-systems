/*
 This is the calibration sketch. Use it to determine the calibration_factor. It also
 outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.

LLC = Left Load Cell, facing the motor mount from the front
RLC = Right Load Cell, facing the motor mount from the front
CF_LLC = Calibration Factor, Left Load Cell
CF_RLC = Calibration Factor, Right Load Cell

 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- to adjust the Right Load Cell Calibration factor of until the output readings match the known weight
 Press a/z to adjust the Right Load Cell Calibration factor of until the output readings match the known weight
 
 Use this calibration_factor on the Data_Logger sketch

 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/

#include "HX711.h"

#define DOUTL  5
#define CLKL  4

HX711 scaleL; // Left Load Cell, facing the motor mount from the front

#define DOUTR  7
#define CLKR  6

HX711 scaleR; // Right Load Cell, facing the motor mount from the front

float calibration_factor_LLC = 129730.56; // right calibration factor for value in N.m // original factor of 114.5 for output in grams, then divided by product of 0.0098065 mm/^2 and 0.09 m 

float calibration_factor_RLC = 129730.56; //// right calibration factor for value in N.m // original factor of 114.5 for output in grams


void setup() {
  Serial.begin(9600);
  scaleL.begin(DOUTL, CLKL);
  scaleR.begin(DOUTR, CLKR);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or - to increase/decrease the LLC calibration factor");
  Serial.println("Press a or z to increase/decrease the RLC calibration factor");

  delay(200);

  scaleL.set_scale();
  scaleR.set_scale();
  
  scaleL.tare(); //Reset the scale to 0
  scaleR.tare(); //Reset the scale to 0
  
  long zero_factor_LLC = scaleL.read_average(); //Get a baseline reading, Left Load Cell
  long zero_factor_RLC = scaleR.read_average(); //Get a baseline reading, Right Load Cell
  
  Serial.print("Zero factor_LLC: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.print(zero_factor_LLC);
  Serial.print("; ");
  Serial.print("Zero factor_RLC: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.print(zero_factor_RLC);
  Serial.println(" ");
}

void loop() {

  scaleL.set_scale(calibration_factor_LLC); //Adjust to this calibration factor
  scaleR.set_scale(calibration_factor_RLC); //Adjust to this calibration factor

  Serial.print("LLC reading: ");
  Serial.print(scaleL.get_units(), 3);
  Serial.print(" N.m"); 
  Serial.print(" CF_LLC: ");
  Serial.print(calibration_factor_LLC);
  Serial.print("; "); 
  Serial.print("RLC reading: ");
  Serial.print(scaleR.get_units(), 3);
  Serial.print(" N.m"); 
  Serial.print(" CF_RLC: ");
  Serial.print(calibration_factor_RLC);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+')
      calibration_factor_RLC += 2.5;
    if(temp == '-')
      calibration_factor_RLC -= 2.5;
    if(temp == 'a')
      calibration_factor_LLC += 2.5;
    else if(temp == 'z')
      calibration_factor_LLC -=2.5;  
  }
}
