# Thermistor
A class for calculating thermistor readings using Steinhart-Hart Model coefficients

The standard Steinhart-Hart Model uses a set 3 coefficients to calculate temperature from a resistance measurement of an NTC thermistor.
The model is as follows:

lnrt = ln (Rt)

Where Rt is the resistance of the thermistor at some temperature t. The temperature can be calculated as follows:

Temp = 1 / (ka + kb*lnrt + kc*lnrt^3)

This library modifies this model slightly and adds an lnrt^2 term (referred to here as kx2):

Temp = 1 / (ka + kb*lnrt + kx2*lnrt^2 + kc*lnrt^3)

The library assumes a circuit where a voltage divider is created using the NTC thermistor and fixed value resistor. The fixed value 
resistor is connected between Vref on the Arduino and one of the analog input pins on the Arduino and the NTC thermistor is connected 
between that analog input pin and ground.

To use the class, a thermistor object is created using the following parameters:

pin - Arduino identifier of the analog input pin in the circuit
rH  - Resistance of the fixed resistor on the high side of the voltage divider circuit
ka  - ka coefficient in the Steinhart-Hart Model
kb  - kb coefficient in the Steinhart-Hart Model
kx2 - coefficient for lnrt^2 (not in the Stienhart-Hart model, but it seems to improve fits)
kc  - kc coefficient in the Steinhart-Hart Model

The library includes the following functions:

double avgThermistor(uint16_t count) - Returns a temperature (in C) from multiple readings (specified by the 
                                        count parameter) of the analog input pin.
                                        
double tempC(double rawReading)      - Returns the temperature (in C) from the 10-bit raw value of an analogRead()
                                       Arduino function. (Note- Assumes your microntroller returns 10-bit values).

Other hopefully helpful things:

Temperature in the Steinhart-Hart equation is in absolute units like Kelvin. These are converted to C by the library.

The resistance of the fixed resistor can be chosen so the voltage returned by the dvider circuit works well at the
tempertature range you expect to be measuring.

Steinhart-Hart coefficients are not typically provided, however you can determine them for the thermistor experimentally using a 
calibrated thermometer or high precision digital sensor like the Ti TMP275 or SiLabs HDC1080. Generally, those digital sensors are
less influenced by drift than thermistors, but by averaging many measurements taken quickly with a thermistor, they can offer
greater precision. 
