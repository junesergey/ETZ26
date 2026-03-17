void markerUp(){
  delay(MarkerDelay);
  markerServo.write(MarkerUp);
  delay(MarkerDelay);
}

void markerDown(){
  delay(MarkerDelay);
  markerServo.write(MarkerDown);
  delay(MarkerDelay);
}