
#include "pingSensor.h"

/*
 * pingSensor( byte trig, byte echo )
 *  Class constructor
 *  Arguments:
 *   trigger pin, echo pin
 *  Uses CONV_CM as the default conversion type, and DEF_PING_DISTANCE for max distance.
 */
pingSensor::pingSensor( byte trig, byte echo ) {
  _trigger = trig;
  _echo = echo;
  _distance = 0;
  _convType = CONV_CM;
  _maxDistance = DEF_PING_DISTANCE;
}

/*
 * pingSensor( byte trig, byte echo, int maxDistance )
 *  Class constructor
 *  Arguments:
 *   trigger pin, echo pin, max distance to detect
 *  Uses CONV_CM as the default conversion type.
 */
pingSensor::pingSensor( byte trig, byte echo, int maxDistance ) {
  _trigger = trig;
  _echo = echo;
  _distance = 0;
  _convType = CONV_CM;
  _maxDistance = maxDistance;
}

/*
 * pingSensor( byte trig, byte echo, int maxDistance, CONVERSION_TYPE convType )
 *  Class constructor
 *  Arguments:
 *   trigger pin, echo pin, measurement conversion type, max distance to detect
 */
pingSensor::pingSensor( byte trig, byte echo, int maxDistance, CONVERSION_TYPE convType ) {
  _trigger = trig;
  _echo = echo;
  _distance = 0;
  _convType = convType;
  _maxDistance = maxDistance;
}

/*
 * void init( void )
 *  Set the pinmodes of the sensor.
 */
void pingSensor::init( void ) {
  pinMode( _trigger, OUTPUT );
  pinMode( _echo, INPUT );
}

/*
 * boolean checkRange( void )
 *  Returns false if the distance is out of range, true if its in range.
 */
boolean pingSensor::checkRange( void ) {
  // Ensure the distance is both below max and above 0.
  if( _distance > _maxDistance || _distance <= 0 ) {
    return false;
  }
  else {
    return true;
  }
}

/*
 * void doPing( void )
 *  Creates and listens for a ping pulse and then converts 
 *  the detected distance into a desired measurement.
 */
void pingSensor::doPing( void ) {
  long duration;
  // The ping pulse is triggered by a HIGH pulse of 10 ms.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite( _trigger, LOW );
  delayMicroseconds( 2 );
  digitalWrite( _trigger, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( _trigger, LOW );

  // The echo pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn( _echo, HIGH );
  
  // Based upon our chosen conversion type, calculate the 
  //  appropriate distance.
  if( _convType == CONV_INCHES ) {
    _distance = msToInches( duration );
  }
  else {
    _distance = msToCm( duration );
  }
}

/*
 * long msToInches( long ms )
 *  Convert microseconds to inches.
 */
long pingSensor::msToInches( long ms ) {
  return ms / 74 / 2;
}

/*
 * long msToCm( long ms )
 *  Convert microseconds to centimeters.
 */
long pingSensor::msToCm( long ms ) {
  return ms / 29 / 2;
}

/*
 * long getDistance( void )
 *  Retrieve the stored last ping distance.
 */
long pingSensor::getDistance( void ) {
  return _distance;
}

/*
 * long getConvType( void )
 *  Retrieve the stored distance conversion type.
 */
long pingSensor::getConvType( void ) {
  return _convType;
}
