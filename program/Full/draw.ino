void drawLineXY(float x, float y){
  markerDown();
  moveXY(x, y);
  markerUp();
}

void drawLineToXY(float x, float y){
  markerDown();
  moveToXY(x, y);
  markerUp();
}

void drawRectangle(float x, float y){
  markerDown();
  moveXY(x, 0);
  delay(500);
  moveXY(0, y);
  delay(500);
  moveXY(-x, 0);
  delay(500);
  moveXY(0, -y);
  delay(500);
  markerUp();
}