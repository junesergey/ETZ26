void kalibrovka(){
  markerScan();
  moveXY(0, 85);
  vivodTCRT(0);
  int f = 0;
  while(f == 0){
    moveXYScan(1, 0);
    vivodTCRT(1);
    delay(10);
    if(analogRead(TCRT1) > grey1){
      f = check(grey1);
    }
  }
  CurrentX = -8;
  moveXY(10, 0);
  moveXY(0, -85);
  f = 0;
  while(f == 0){
    moveXYScan(0, 1);
    vivodTCRT(3);
    delay(10);
    if(analogRead(TCRT1) > grey12){
      f = check(grey12);
    }
  }
  moveXY(0,24);
  markerDown();
  delay(500);
  markerUp();
  CurrentX = 0.0f;
  CurrentY = 0.0f;
  delay(1000);
}

int check(int grey){
  int r = 0;
  for(int i = 0; i < 7; i++){
    vivodTCRT(2);
    if(analogRead(TCRT1) > grey){
      r += 1;
    }
    delay(100);
  }
  if(r >= 6){
    return 1;
  }
  else{
    return 0;
  }
}