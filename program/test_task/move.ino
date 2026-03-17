void moveX(int x){
  float iterations = x * Iter_Per_Milli_X;
  if (iterations < 0){
    iterations = abs(iterations);
    digitalWrite(DIR_PIN_X, LOW);
  }
  else{
    digitalWrite(DIR_PIN_X, HIGH);
  }
  while(iterations > 0){
    digitalWrite(STEP_PIN_X, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP_PIN_X, LOW);
    delayMicroseconds(200);
    iterations -= 1;
  }
}

void moveY(int y){
  float iterations = y * Iter_Per_Milli_Y;
  if (iterations < 0){
    iterations = abs(iterations);
    digitalWrite(DIR_PIN_Y, HIGH);
  }
  else{
    digitalWrite(DIR_PIN_Y, LOW);
  }
  while(iterations > 0){
    digitalWrite(STEP_PIN_Y, HIGH);
    delayMicroseconds(50);
    digitalWrite(STEP_PIN_Y, LOW);
    delayMicroseconds(50);
    iterations -= 1;
  }
}