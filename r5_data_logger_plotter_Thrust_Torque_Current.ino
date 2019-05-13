/* this sketch is used together with the MegunoLink software which will allow to visualise the data as it comes and then export it if desired 
 */

#include "HX711.h" // HX711 library

#include <MegunoLink.h> // MegunoLink library

#define calibration_factor_F 22127.84 // This value is obtained using the SparkFun_HX711_Thrust_Calibration sketch // 137.50 // 217
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

float Sensibility=0.46; //sensibility in Volts/Amps for the 30A sensor

// /* code for data plot
long LastSent;
const unsigned SendInterval = 200; // [ms] //originally: 200 [ms] 

XYPlot MyPlot;
// */ end code for data plot

void setup() {
  Serial.begin(9600);
// /* code for data plot
  LastSent = millis();
  
  MyPlot.Clear();
  // MyPlot.SetTitle("Thrust [N], Torque [Nm], Current [A] against Time [s]");
  MyPlot.SetTitle("Thrust [N], Torque [Nm] against Time [s]");
  MyPlot.SetXlabel("Time, [s]");
  // MyPlot.SetYlabel("Thrust [N], Torque [Nm], Current [A]");
  MyPlot.SetYlabel("Thrust [N], Torque [Nm]");
  MyPlot.SetSeriesProperties("Thrust [N]", Plot::Magenta, Plot::Solid, 2, Plot::Square);
  // MyPlot.SetSeriesProperties("Current [A]", Plot::Blue, Plot::Solid, 2, Plot::Triangle);
  MyPlot.SetSeriesProperties("Torque [Nm]", Plot::Green, Plot::Solid, 2, Plot::Circle);
// */ end code for data plot

  scale.begin(DOUT, CLK); // begin Load Cell 1
  scaleL.begin(DOUTL, CLKL); // begin Load Cell L
  scaleR.begin(DOUTR, CLKR); // begin Load Cell R
  
  Serial.println("Thrust [N], Torque [Nm], Current [A] Test Bench demo");

  scale.set_scale(calibration_factor_F); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scaleL.set_scale(calibration_factor_T);
  scaleR.set_scale(calibration_factor_T);
  
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scaleL.tare();
  scaleR.tare();
 
}

void loop() {

// /* code for data plotter
    if ((millis() - LastSent) > SendInterval)
  {
    LastSent = millis();
 // */ end code for data plotter

    float voltaGeSensor = analogRead(A0)*(5.0 / 1023.0); //Hall sensor reading  
//    float current =(voltaGeSensor-2.5)/Sensibility; //equation for obtaining current
  
    float time = (float)millis()/1000;
    float thrust = scale.get_units(); //
    float torque = ((scaleL.get_units()+ scaleR.get_units())/2); // c
   
    Serial.println();
    MyPlot.SendData("Thrust [N]", time, thrust, 3); // comment if MegunoLink is not used and use serial port for .csv file
   //  MyPlot.SendData("Current [A]", time, current, 3);
    MyPlot.SendData("Torque [Nm]", time, torque, 3);
  }
}
