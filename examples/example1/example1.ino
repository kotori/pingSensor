/*
 * pingSensor example #1
 *  This sketch demonstrates the pingSensor library with a 4-pin PING sensor.
 */
#include <pingSensor.h>

#define TRIG 4
#define ECHO 5
#define MAX_DISTANCE 30

// Create object
pingSensor *pingsense;

void setup() {
  // Open serial interface.
  Serial.begin(9600);

  // setup pingSensor object.
  // defaults to 'cm' units of measurement.
  pingsense = new pingSensor(TRIGGER_PIN, ECHO_PIN, MAX_PING_DISTANCE);
}

void loop() {
  pingsense->doPing();
  if(pingsense->checkRange()) {
    Serial.print("Object detected at ");
    Serial.print(pingsense->getDistance());
    Serial.println(" cm");
  }
  delay(500);
}

