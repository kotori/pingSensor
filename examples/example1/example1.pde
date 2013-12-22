
#include <pingSensor.h>

#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define MAX_PING_DISTANCE 30

// Create object
pingSensor *myPinger;

void setup() {
  // Open serial interface.
  Serial.begin(9600);

  // setup pingSensor object.
  // defaults to 'cm' units of measurement.
  myPing = new pingSensor(TRIGGER_PIN, ECHO_PIN, MAX_PING_DISTANCE);
}

void loop() {
  myPinger->doPing();
  if(myPinger->checkRange()) {
    Serial.print("Object detected at ");
    Serial.print(myPinger->getDistance());
    Serial.println(" cm");
  }
  delay(500);
}

