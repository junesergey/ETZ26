
#include <Servo.h>

extern Servo markerServo;
extern const float MarkerUp;
extern const float MarkerDown;
extern const float MarkerScan;
extern const uint16_t MarkerDelay;

void markerUp() {
  delay(MarkerDelay);
  markerServo.write(MarkerUp);
  delay(MarkerDelay);
}

void markerDown() {
  delay(MarkerDelay);
  markerServo.write(MarkerDown);
  delay(MarkerDelay);
}

void markerScan() {
  delay(MarkerDelay);
  markerServo.write(MarkerScan);
  delay(MarkerDelay);
}