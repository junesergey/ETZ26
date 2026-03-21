void markerDown();
void markerUp();

void moveXY(float dx, float dy);
void moveToXY(float x, float y);


void drawLineXY(float dx, float dy) {
  markerDown();
  moveXY(dx, dy);
  markerUp();
}

void drawLineToXY(float x, float y) {
  markerDown();
  moveToXY(x, y);
  markerUp();
}

void drawPoint() {
  markerDown();
  delay(200);
  markerUp();
}

void drawRectangle(float dx, float dy){
  moveXY(dx/2, -dy/2);
  markerDown();
  moveXY(-dx, 0);
  moveXY(0, dy);
  moveXY(dx, 0);
  moveXY(0, -dy);
  markerUp();
  moveXY(-dx/2, dx/2);
}

void drawCircle(float radius) {
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float prevX = cx + radius;
  float prevY = cy;
  moveXY(radius, 0);
  markerDown();
  for (int i = 1; i <= 360; i++) {
    float angle = i * angleStep;
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);
    moveXY(x - prevX, y - prevY);
    prevX = x;
    prevY = y;
  }
  markerUp();
  moveXY(-radius, 0);
}

void drawArc(float radius, float startAngle, float finishAngle){
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float startAngleStep = angleStep * startAngle;
  float finishAngleStep = angleStep * finishAngle;
  float prevX = cx + radius * cos(startAngleStep);
  float prevY = cy + radius * sin(startAngleStep);
  moveXY(radius * cos(startAngleStep), radius * sin(startAngleStep));
  markerDown();
  for (int i = startAngle; i <= finishAngle; i++) {
    float angle = i * angleStep;
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);
    moveXY(x - prevX, y - prevY);
    prevX = x;
    prevY = y;
  }
  markerUp();
  moveXY(-radius * cos(finishAngleStep), -radius * sin(finishAngleStep));
}