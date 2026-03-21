extern volatile float CurrentX;
extern volatile float CurrentY;

extern float Speed;
extern const float IterPerMilliX;
extern const float IterPerMilliY;

void stepPulse(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(pin, LOW);
}

long mmToStepsX(float mm) {
  return lroundf(mm * IterPerMilliX);
}
long mmToStepsY(float mm) {
  return lroundf(mm * IterPerMilliY);
}


void moveXY(float dx_mm, float dy_mm) {
  long stepsX = mmToStepsX(dx_mm);
  long stepsY = mmToStepsY(dy_mm);

  if (stepsX == 0 && stepsY == 0) return;

  if (stepsX < 0) digitalWrite(DIR_PIN_X, HIGH);
  else digitalWrite(DIR_PIN_X, LOW);

  if (stepsY < 0) digitalWrite(DIR_PIN_Y, LOW);
  else digitalWrite(DIR_PIN_Y, HIGH);

  delayMicroseconds(5);

  long ax = labs(stepsX);
  long ay = labs(stepsY);

  float dist = sqrtf(dx_mm * dx_mm + dy_mm * dy_mm);
  if (dist < 1e-6f) return;

  float v = Speed;
  if (v < 1.0f) v = 1.0f;

  float time_s = dist / v;
  long major = max(ax, ay);
  if (major < 1) major = 1;

  uint32_t stepIntervalUs = (uint32_t)lroundf((time_s * 1000000.0f) / (float)major);

  if (stepIntervalUs < 300) stepIntervalUs = 300;

  if (ax >= ay) {
    long err = ax / 2;
    for (long i = 0; i < ax; i++) {
      stepPulse(STEP_PIN_X);

      err += ay;
      if (err >= ax) {
        err -= ax;
        if (ay) stepPulse(STEP_PIN_Y);
      }

      delayMicroseconds(stepIntervalUs);
    }
  } else {
    long err = ay / 2;
    for (long i = 0; i < ay; i++) {
      stepPulse(STEP_PIN_Y);

      err += ax;
      if (err >= ay) {
        err -= ay;
        if (ax) stepPulse(STEP_PIN_X);
      }

      delayMicroseconds(stepIntervalUs);
    }
  }

  CurrentX += (float)stepsX / IterPerMilliX;
  CurrentY += (float)stepsY / IterPerMilliY;
}

void moveX(float dx_mm) {
  moveXY(dx_mm, 0.0f);
}
void moveY(float dy_mm) {
  moveXY(0.0f, dy_mm);
}

void moveToXY(float x_mm, float y_mm) {
  float dx = x_mm - CurrentX;
  float dy = y_mm - CurrentY;
  moveXY(dx, dy);
}

void moveXYScan(float dx_mm, float dy_mm) {
  long stepsX = mmToStepsX(dx_mm);
  long stepsY = mmToStepsY(dy_mm);

  if (stepsX == 0 && stepsY == 0) return;

  if (stepsX < 0) digitalWrite(DIR_PIN_X, HIGH);
  else digitalWrite(DIR_PIN_X, LOW);

  if (stepsY < 0) digitalWrite(DIR_PIN_Y, LOW);
  else digitalWrite(DIR_PIN_Y, HIGH);

  delayMicroseconds(5);

  long ax = labs(stepsX);
  long ay = labs(stepsY);

  float dist = sqrtf(dx_mm * dx_mm + dy_mm * dy_mm);
  if (dist < 1e-6f) return;

  float v = SpeedScan;
  if (v < 1.0f) v = 1.0f;

  float time_s = dist / v;
  long major = max(ax, ay);
  if (major < 1) major = 1;

  uint32_t stepIntervalUs = (uint32_t)lroundf((time_s * 1000000.0f) / (float)major);

  if (stepIntervalUs < 300) stepIntervalUs = 300;

  if (ax >= ay) {
    long err = ax / 2;
    for (long i = 0; i < ax; i++) {
      stepPulse(STEP_PIN_X);

      err += ay;
      if (err >= ax) {
        err -= ax;
        if (ay) stepPulse(STEP_PIN_Y);
      }

      delayMicroseconds(stepIntervalUs);
    }
  } else {
    long err = ay / 2;
    for (long i = 0; i < ay; i++) {
      stepPulse(STEP_PIN_Y);

      err += ax;
      if (err >= ay) {
        err -= ay;
        if (ax) stepPulse(STEP_PIN_X);
      }

      delayMicroseconds(stepIntervalUs);
    }
  }

  CurrentX += (float)stepsX / IterPerMilliX;
  CurrentY += (float)stepsY / IterPerMilliY;
}