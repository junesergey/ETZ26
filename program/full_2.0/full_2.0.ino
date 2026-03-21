#include <Servo.h>
#include <Wire.h>

#define STEP_PIN_X 40
#define DIR_PIN_X 42
#define STEP_PIN_Y 32
#define DIR_PIN_Y 34
#define MARKER_PIN 8

#define LED_PIN 13

#define TCRT1 A5
#define TCRT2 A8

#define BUTTON_PIN_SELLECT 24
#define BUTTON_PIN_NEXT 26
#define BUTTON_PIN_PREV 28

// серва
static const float MarkerUp = 5;
static const float MarkerDown = 50;
static const float MarkerScan = 25;
static const uint16_t MarkerDelay = 300;  // ms

static float Speed = 100.0f;
static float SpeedScan = 25.0f;

//#############################################
static const float kX = 81.0f / 74.0f;
static const float kY = 70.0f / 73.0f;

//##########################################
static const float IterPerMilliX = (200.0f * 16.0f) / (48.0f * 3.14f) * kX;
static const float IterPerMilliY = (200.0f * 16.0f) / (12.2f * 3.14f) * kY;

volatile float CurrentX = 0.0f;
volatile float CurrentY = 0.0f;

static int grey1 = 35;
static int grey12 = 37;
static int grey2 = 35;

Servo markerServo;

void markerUp();
void markerDown();
void markerScan();

void moveX(float dx);
void moveY(float dy);
void moveXY(float dx, float dy);
void moveToXY(float x, float y);

void drawLineXY(float x, float y);
void drawLineToXY(float x, float y);
void drawRectangle(float x, float y);

void setup() {
  Serial.begin(115200);

  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN_SELLECT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_NEXT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_PREV, INPUT_PULLUP);

  markerServo.attach(MARKER_PIN);
  delay(300);
  markerServo.write(MarkerUp);
  delay(300);
  
  display();
  int mode = sellectMode();
  Serial.print("Mode_Sellect: ");
  Serial.println(mode);
  kalibrovka();
  switch(mode){
    case 0:
      moveToXY(100, 100);
      moveX(50);
      moveY(-50);

      moveX(-50);
      moveY(50);

      for (int i = 50; i >= -50; i -= 10) {
        drawLineXY(50, -i);
        moveXY(-50, i);
      }
      for (int i = 40; i >= -50; i -= 10) {
        drawLineXY(i, 50);
        moveXY(-i, -50);
      }

      for (int i = 50; i >= -50; i -= 10) {
        drawLineXY(-50, i);
        moveXY(50, -i);
      }
      for (int i = 50; i >= -50; i -= 10) {
        drawLineXY(-i, -50);
        moveXY(i, 50);
      }
      markerUp();
      break;
    case 1:
      moveToXY(80, 80);
      drawPoint();
      drawSemicircleRight(20);
      moveToXY(90, 80);
      drawSemicircleLeft(30);
      break;
    case 2:
      moveToXY(170, 20);
      drawPoint();
      drawArc(20, 45, 315);
      drawPoint();
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
  }
}

void loop() {
}