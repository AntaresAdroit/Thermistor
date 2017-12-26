#include <Thermistor.h>

Thermistor bath(A0, 10000, 7.59274E-04, 2.14411E-04, -5.47089E-07, 1.29089E-07);
Thermistor air(A1, 10000, 1.85776E-03, 2.12327E-05, 2.27316E-05, -7.74693E-07);

void setup() {
  Serial.begin(115200);

}

void loop() {
  double t;
  //t = bath.avgThermistor(2);
  //t = air.avgThermistor(2);
  Serial.print(bath.avgThermistor(10));
  Serial.print(" ");
  Serial.println(air.avgThermistor(10));
  delay(1000);

}
