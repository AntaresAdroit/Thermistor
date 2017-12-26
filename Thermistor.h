#ifndef Thermistor_h
#define Thermistor_h

#include <Arduino.h>

class Thermistor
{
  public:
	Thermistor(uint8_t pin, uint16_t rH, double ka, double kb, double kx2, double kc);
	double rThermistor(double rawReading);
	double tempC(double rawReading);
	double avgThermistor(uint16_t count);
	
  protected:
    double _ka, _kb, _kx2, _kc;
    uint8_t _pin;
    uint16_t _rH;
};


#endif