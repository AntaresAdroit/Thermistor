//Basic demonstration of how to use the library
//Takes measurements from 2 separate thermistors and
//prints them to the serial port. Each reading is an
//average of 10 measurements.

#include <Thermistor.h>

//Create two thermistors, one on pin A0 and one on pin A1
//Parameters: (analog pin, fixed resistor value, ka, kb, kx2, kc)
Thermistor bath(A0, 10000, 7.59274E-04, 2.14411E-04, -5.47089E-07, 1.29089E-07);
Thermistor air(A1, 10000, 1.85776E-03, 2.12327E-05, 2.27316E-05, -7.74693E-07);

void setup() {
  Serial.begin(115200);

}

void loop() {
  Serial.print(bath.avgThermistor(10));
  Serial.print(" ");
  Serial.println(air.avgThermistor(10));
  delay(1000);

}
