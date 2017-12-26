#include <Thermistor.h>

// Constructors ////////////////////////////////////////////////////////////////

  Thermistor::Thermistor(uint8_t pin, uint16_t rH, double ka, double kb, double kx2, double kc)
  {
    _pin = pin;
    _ka = ka; 
    _kb = kb;
    _kx2 = kx2;
    _kc = kc;
    _rH = rH;
  }
  
  
  double Thermistor::rThermistor(double rawReading){
    double voltageFraction;
    voltageFraction = ( rawReading )/1023.0;
    return voltageFraction * _rH / ( 1.0 - voltageFraction);
  }

  double Thermistor::tempC(double rawReading){
    double lnR = log(rThermistor(rawReading));
    return 1 / ( _ka + (_kb * lnR) + (_kx2 * lnR * lnR) + (_kc * lnR * lnR * lnR) ) - 273.15;
  }

  double Thermistor::avgThermistor(uint16_t count){
    uint32_t avgTempC;                 
    avgTempC = 0;
    for(uint16_t i = 0; i < count; i++){
      avgTempC = avgTempC + analogRead(_pin);
    }
    return tempC(avgTempC / double(count));
  }