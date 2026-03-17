#include <Servo.h>

#define STEP_PIN_X 40
#define DIR_PIN_X 42
#define STEP_PIN_Y 32
#define DIR_PIN_Y 34
#define MARKER_PIN 8

#define LED_PIN 13

#define TCRT1 A5
#define TCRT2 A8

#define BUTTON_PIN 24

static const float Marker_Up = 5;
static const float Marker_Down = 50;

static const float Iter_Per_Milli_X = (200 * 16) / (48 * 3.14);
static const float Iter_Per_Milli_Y = (200 * 16) / (12.2 * 3.14);

Servo markerServo;

void setup() {
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  markerServo.attach(MARKER_PIN);
  delay(1000);
  markerServo.write(Marker_Up);
  delay(500);

while (digitalRead(BUTTON_PIN) == 1);
  digitalWrite(LED_PIN, HIGH);

  markerDown();
  moveX(150);
  delay(1000);
  moveY(150);
  markerUp();
  moveY(-150);
  delay(1000);
  moveX(-150);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

void loop() {
}