# Testing-device-for-small-electrical-propulsion-systems
  This project was carried out for the final year individual project for Aerospace Engineering (BEng) at the University of Surrey.

The following libraries are required for the script:

https://github.com/bogde/HX711 [library for the HX711 voltage amplifier connected to the load cells]

https://github.com/Megunolink/MLP [library for the program (MegunoLink) used to plot real time data from the sensors / required for script 4 only]

This set up uses 3 load cells (TAL220) to measure thrust and torques from a BLDC motor and propeller combination, and a ACS712 (30A) hall sensor for measuring current.

The connections to the Arduino required are as follows:

  The data and clock ports for the thrust load cell and voltage amplifier are conencted to ports 2 and 3 in the Arduino.
  The data and clock ports for the left torque load cell and voltage amplifier are conencted to ports 4 and 5 in the Arduino.
  The data and clock ports for the right torque cell and voltage amplifier are conencted to ports 6 and 7 in the Arduino.
  All the power and ground connections of load cells are connected to a breadboard where the power and ground ports of the Arduino are connected too. Use the 5V port.
  The analog In port on the current sensor is connected to the analog input A0 in the Arduino board. The ground and power options are connected too to the same rales in the breadboard as the load cells.
  

