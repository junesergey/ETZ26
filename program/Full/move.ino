void moveX(float x) {
  CurrentX += x;

  long Iterations = x * IterPerMilliX;
  if (Iterations < 0) {
    Iterations = abs(Iterations);
    digitalWrite(DIR_PIN_X, HIGH);
  } else {
    digitalWrite(DIR_PIN_X, LOW);
  }
  while (Iterations > 0) {
    digitalWrite(STEP_PIN_X, HIGH);
    delayMicroseconds(StepDelayX);
    digitalWrite(STEP_PIN_X, LOW);
    delayMicroseconds(StepDelayX);
    Iterations -= 1;
  }
}

void moveY(float y) {
  CurrentY += y;

  long Iterations = y * IterPerMilliY;
  if (Iterations < 0) {
    Iterations = abs(Iterations);
    digitalWrite(DIR_PIN_Y, LOW);
  } else {
    digitalWrite(DIR_PIN_Y, HIGH);
  }
  while (Iterations > 0) {
    digitalWrite(STEP_PIN_Y, HIGH);
    delayMicroseconds(StepDelayY);
    digitalWrite(STEP_PIN_Y, LOW);
    delayMicroseconds(StepDelayY);
    Iterations -= 1;
  }
}

void moveXY(float x, float y) {
  if (x == 0) {
    moveY(y);
  } else if (y == 0) {
    moveX(x);
  } else {
    CurrentX += x;
    CurrentY += y;
    IterationsX = x * IterPerMilliX;
    IterationsY = y * IterPerMilliY;

    if (IterationsX < 0) {
      IterationsX = abs(IterationsX);
      digitalWrite(DIR_PIN_X, HIGH);
    } else {
      digitalWrite(DIR_PIN_X, LOW);
    }

    if (IterationsY < 0) {
      IterationsY = abs(IterationsY);
      digitalWrite(DIR_PIN_Y, LOW);
    } else {
      digitalWrite(DIR_PIN_Y, HIGH);
    }

    float TimeX = 2 * StepDelayX * IterationsX;
    float TimeY = 2 * StepDelayY * IterationsY;
    float TimeXY = max(TimeX, TimeY);
    float StepDelayXUmn = StepDelayX * TimeXY / TimeX;
    float StepDelayYUmn = StepDelayY * TimeXY / TimeY;

    StepStateX = HIGH;
    StepStateY = HIGH;
    unsigned long LastChangeStepX = micros();
    unsigned long LastChangeStepY = micros();

    Serial.println("X:");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(IterationsX * StepDelayXUmn);
    Serial.println(IterationsX / IterPerMilliX);
    Serial.println(StepDelayXUmn);
    Serial.println(IterationsX);

    Serial.println("Y:");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(IterationsY * StepDelayYUmn);
    Serial.println(IterationsY / IterPerMilliY);
    Serial.println(StepDelayYUmn);
    Serial.println(IterationsY);


    uint32_t myTime = micros();
    while (IterationsX > 0 || IterationsY > 0) {
      if (micros() - LastChangeStepY >= StepDelayYUmn) {
        changeStepY();
        LastChangeStepY = micros();
      }
      if (micros() - LastChangeStepX >= StepDelayXUmn) {
        changeStepX();
        LastChangeStepX = micros();
      }
      
    }
    // delay(10);
    Serial.println(micros() - LastChangeStepX);
    Serial.println(micros() - LastChangeStepY);

    delayMicroseconds(min(StepDelayXUmn, StepDelayYUmn));
    Serial.println("Itog: ");
    Serial.print("IterationsX: ");
    Serial.println(IterationsX);
    Serial.print("IterationsY: ");
    Serial.println(IterationsY);

    Serial.println(" ");
  }
}

void moveToXY(float NeededX, float NeededY) {
  float deltaX = NeededX - CurrentX;
  float deltaY = NeededY - CurrentY;
  moveXY(deltaX, deltaY);
}