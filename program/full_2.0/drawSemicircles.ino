//не знаю нужны ли они, когда есть drawArc
void drawSemicircleDown(float radius) {
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float prevX = cx + radius;
  float prevY = cy;
  moveXY(radius, 0);
  markerDown();
  for (int i = 1; i <= 180; i++) {
    float angle = i * angleStep;
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);
    moveXY(x - prevX, y - prevY);
    prevX = x;
    prevY = y;
  }
  markerUp();
  moveXY(radius, 0);
}

void drawSemicircleUp(float radius) {
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float prevX = cx - radius;
  float prevY = cy;
  moveXY(-radius, 0);
  markerDown();
  for (int i = 180; i <= 360; i++) {
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

void drawSemicircleRight(float radius) {
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float prevX = cx;
  float prevY = cy - radius;
  moveXY(0, -radius);
  markerDown();
  for (int i = 270; i <= 450; i++) {
    float angle = i * angleStep;
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);
    moveXY(x - prevX, y - prevY);
    prevX = x;
    prevY = y;
  }
  markerUp();
  moveXY(0, -radius);
}

void drawSemicircleLeft(float radius) {
  float cx = CurrentX;
  float cy = CurrentY;
  float angleStep = 2 * PI / 360.0;
  float prevX = cx;
  float prevY = cy + radius;
  moveXY(0, radius);
  markerDown();
  for (int i = 90; i <= 270; i++) {
    float angle = i * angleStep;
    float x = cx + radius * cos(angle);
    float y = cy + radius * sin(angle);
    moveXY(x - prevX, y - prevY);
    prevX = x;
    prevY = y;
  }
  markerUp();
  moveXY(0, radius);
}