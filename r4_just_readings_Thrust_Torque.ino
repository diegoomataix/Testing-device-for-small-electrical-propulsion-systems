#include "HX711.h" // HX711 library


#define calibration_factor_F 22127.84 // This value is obtained using the SparkFun_HX711_Thrust_Calibration sketch
#define calibration_factor_T 129730.56 // This value is obtained using the SparkFun_HX711_Torque_Calibration sketch

#define DOUT  3 // Defines DATA port for Load Cell 1, thrust
#define CLK  2 // Defines CLK port for Load Cell 1, thrust

HX711 scale;

#define DOUTL  5 // Defines DATA port for Load Cell L, torque
#define CLKL  4 // Defines CLK port for Load Cell L, torque

HX711 scaleL;

#define DOUTR  7 // Defines DATA port for Load Cell R, torque
#define CLKR  6 // Defines CLK port for Load Cell R, torque

HX711 scaleR;

int count = 0;
unsigned long time;

float Sensibility=0.66; //sensibility in Volts/Amps for the 30A sensor


void setup() {
  Serial.begin(9600);


  scale.begin(DOUT, CLK); // begin Load Cell 1
  scaleL.begin(DOUTL, CLKL); // begin Load Cell L
  scaleR.begin(DOUTR, CLKR); // begin Load Cell R
  
 // Serial.println("Thrust [N], Torque [Nm], Current [A] Test Bench");
  Serial.println("Thrust [N], Torque [Nm] Test Bench");
  
  scale.set_scale(calibration_factor_F); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scaleL.set_scale(calibration_factor_T);
  scaleR.set_scale(calibration_factor_T);
  
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scaleL.tare();
  scaleR.tare();
  
  Serial.println("Readings: Time [s], Thrust [N], Torque [Nm], Current [A"); // uncomment out if Serial Monitor will be used

}

void loop() {

    float voltaGeSensor = analogRead(A0)*(5.0 / 1023.0); //Hall sensor reading  
    float current =(voltaGeSensor-2.5)/Sensibility; //equation for obtaining current
  
    float time = (float)millis()/1000;
    float thrust = scale.get_units(); // 0.00980665f = 9.80665 m/s^2 / 1000 
    float torque = (scaleL.get_units()+ scaleR.get_units())/2; // 0.000784532f 9.80665 m/s^2 * 0.08 m / 1000) 
   
    Serial.print(time, 1); 
    Serial.print(",");
    Serial.print(thrust, 2);
    Serial.print(",");
    Serial.print(torque, 3);
    Serial.print(",");
    // Serial.print(current, 2);
    Serial.println();
}
