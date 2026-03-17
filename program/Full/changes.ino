void changeStepX(){
  if(StepStateX == LOW){
    digitalWrite(STEP_PIN_X, HIGH);
    StepStateX = HIGH;
  }
  else{
    digitalWrite(STEP_PIN_X, LOW);
    StepStateX = LOW;
    IterationsX -= 1;
  }
}

void changeStepY(){
  if(StepStateY == LOW){
    digitalWrite(STEP_PIN_Y, HIGH);
    StepStateY = HIGH;
  }
  else{
    digitalWrite(STEP_PIN_Y, LOW);
    StepStateY = LOW;
    IterationsY -= 1;
  }
}