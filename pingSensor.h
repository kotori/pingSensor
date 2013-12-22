
#ifndef pingSensor_h
#define pingSensor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

const int DEF_PING_DISTANCE = 200;

enum CONVERSION_TYPE {
  CONV_INCHES = 0, // Conversions are in inches.
  CONV_CM = 1 // Conversions are in centimeters.
};

class pingSensor {
public:

  pingSensor( byte trig, byte echo );
  pingSensor( byte trig, byte echo, int maxDistance );
  pingSensor( byte trig, byte echo, int maxDistance, CONVERSION_TYPE convType );
  
  void doPing( void );
  
  long getDistance( void );
  
  long getConvType( void );
  
  boolean checkRange( void );
  
private:
  void init( void );

  long msToInches( long ms );
  long msToCm( long ms );

  CONVERSION_TYPE _convType;
  int _maxDistance;
  byte _trigger;
  byte _echo;
  long _distance;
};

#endif // pingSensor_h
