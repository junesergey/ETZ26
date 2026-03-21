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

static const float MarkerUp = 5;
static const float MarkerDown = 50;
static const float MarkerDelay = 1000;

volatile float CurrentX = 0.0;
volatile float CurrentY = 0.0;

static const float Speed = 80;
static const float kX = 80.0/74.0;
static const float kY = 70.0/73.0;
static const float IterPerMilliX = (200 * 16) / (48 * 3.14) * kX; //22.95
static const float IterPerMilliY = (200 * 16) / (12.2 * 3.14) * kY; //80.10

static const float StepDelayX = 1000000 / (2 * Speed * IterPerMilliX);
static const float StepDelayY = 1000000 / (2 * Speed * IterPerMilliY);

volatile bool StepStateX = LOW;
volatile bool StepStateY = LOW;

volatile long IterationsY = 0;
volatile long IterationsX = 0;
volatile long Iterations = 0;

Servo markerServo;

void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  markerServo.attach(MARKER_PIN);
  delay(1000);
  markerServo.write(MarkerUp);
  delay(500);

  while (digitalRead(BUTTON_PIN) == 1);
  // digitalWrite(LED_PIN, HIGH);
  // delay(1000);
  // int f = 0;
  // while(f <= 100){
  //   drawLineXY(100, -f);
  //   delay(500);
  //   moveXY(-100, f);
  //   f += 10;
  // }
  
  // for(int i = 1; i <= 10; i++){
  //   drawLineXY(- i * 10, 0);
  //   moveX(i * 10);
  //   delay(500);
  //   moveY(10);
  //   delay(500);
  // }
  // drawRectangle(50, 50);
  // drawLineXY(50, 50);
  // moveX(50);
  // moveY(-50);
  
  // drawRectangle(-100, 100);

  // moveX(-50);
  // moveY(50);

  drawLineXY_Brench(-50, -50);

  // drawRectangle(-100, 100);
  
  // for(int i = 50; i >= -50; i -= 10){
  //   drawLineXY(50, -i);
  //   moveXY(-50, i);
  // }
  // for(int i = 50; i >= -50; i -= 10){
  //   drawLineXY(i, 50);
  //   moveXY(-i, -50);
  // }

  // for(int i = 50; i >= -50; i -= 10){
  //   drawLineXY(-50, i);
  //   moveXY(50, -i);
  // }
  // for(int i = 50; i >= -50; i -= 10){
  //   drawLineXY(-i, -50);
  //   moveXY(i, 50);
  // }
  
}

void loop() {
}