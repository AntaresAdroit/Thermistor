#include <Thermistor.h>

// Constructors ////////////////////////////////////////////////////////////////
/*
pin - Arduino identifier of the analog input pin in the circuit
rH  - Resistance of the fixed resistor on the high side of the voltage divider circuit
ka  - ka coefficient in the Steinhart-Hart Model
kb  - kb coefficient in the Steinhart-Hart Model
kx2 - coefficient for lnrt^2 (not in the Stienhart-Hart model, but it seems to improve fits)
kc  - kc coefficient in the Steinhart-Hart Model
*/

  Thermistor::Thermistor(uint8_t pin, uint16_t rH, double ka, double kb, double kx2, double kc)
  {
    _pin = pin;
    _ka = ka; 
    _kb = kb;
    _kx2 = kx2;
    _kc = kc;
    _rH = rH;
  }
  
// Public Methods //////////////////////////////////////////////////////////////  

  //Returns the resistance of a thermistor given a double value (from 0 to 1023)
  //represinting the fraction of Vref at the input pin. This is mainly a helper
  //function for tempC()
  double Thermistor::rThermistor(double rawReading){
    double voltageFraction;
    voltageFraction = ( rawReading )/1023.0;
    return voltageFraction * _rH / ( 1.0 - voltageFraction);
  }
  
  //Returns the temperature of a thermistor in C given a double value (from 0 to 1023)
  //represinting the fraction of Vref at the input pin. 
  double Thermistor::tempC(double rawReading){
    double lnR = log(rThermistor(rawReading));
    return 1 / ( _ka + (_kb * lnR) + (_kx2 * lnR * lnR) + (_kc * lnR * lnR * lnR) ) - 273.15;
  }

  //Returns the temperature of a thermistor in C from multiple readings of the analog input
  //pin. The number of readings is specified by the samples parameter.
  double Thermistor::avgThermistor(uint16_t samples){
    uint32_t avgTempC;                 
    avgTempC = 0;
    for(uint16_t i = 0; i < samples; i++){
      avgTempC = avgTempC + analogRead(_pin);
    }
    return tempC(avgTempC / double(samples));
  }
