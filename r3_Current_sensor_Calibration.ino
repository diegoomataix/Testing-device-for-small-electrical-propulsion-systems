float Sensibility=0.66; //sensibility in Volts/Amps for the 30A sensor

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  float voltaGeSensor= analogRead(A0)*(5.0 / 1023.0); //sensor reading  
  float I=(voltaGeSensor-2.5)/Sensibility; //equation for obtaining current
  Serial.print("Current: ");
  Serial.println(I,3); 
  delay(200);     
}
