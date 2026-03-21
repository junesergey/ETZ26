byte numbers_one[10][10]{
  {
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b10000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111
  },
  {
    0b00001100,
    0b00011100,
    0b00111100,
    0b01101100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100
  },
  {
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111111,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111111
  },
  {
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111111
  },
  {
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000011
  },
  {
    0b11111111,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111111
  },
  {
    0b11111111,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111
  },
  {
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000110,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100
  },
  {
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111
  },
  {
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b00000011,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111111
  }
};

void ris(int page, int x, byte* data){
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(0xB0 + page);
  Wire.write(0x00 + (x & 0x0F));
  Wire.write(0x10 + (x>>4 & 0x0F));
  Wire.endTransmission();

  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  for(int i = 0; i < 10; i++){
    if(i % 16 == 0){
      Wire.endTransmission();
      Wire.beginTransmission(0x3C);
      Wire.write(0x40);
    }
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

void initializDis(){
  Wire.begin();
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(0xA8);
  Wire.write(0x3F);
  Wire.write(0xD3);
  Wire.write(0x00);
  Wire.write(0x40);
  Wire.write(0xA1);
  Wire.write(0xC8);
  Wire.write(0xDA);
  Wire.write(0x12);
  Wire.write(0x81);
  Wire.write(0x7F);
  Wire.write(0xA4);
  Wire.write(0xA6);
  Wire.write(0xD5);
  Wire.write(0x80);
  Wire.write(0x8D);
  Wire.write(0x14);
  Wire.write(0xAF);
  Wire.endTransmission();
}

void cleanDis(){
  for(int page = 0; page < 8; page++){
    for(int k = 0; k < 8; k++){
      Wire.beginTransmission(0x3C);
      Wire.write(0x00);
      Wire.write(0xB0 + page);
      int x = k * 16;
      Wire.write(0x00 + (x & 0x0F));
      Wire.write(0x10 + (x>>4 & 0x0F));
      Wire.endTransmission();

      Wire.beginTransmission(0x3C);
      Wire.write(0x40);
      for(int i = 0; i < 16; i++){
        Wire.write(0x00);
      }
      Wire.endTransmission();
    }
  }  
}

void display(){
  initializDis();
  cleanDis();
  ris(5, 5, numbers_one[0]);
}


int sellectMode(){
  int mode = 0;
  while (digitalRead(BUTTON_PIN_SELLECT) == 1){
    if (digitalRead(BUTTON_PIN_NEXT) == 0){
      mode += 1;
      mode = min(10, mode);
      while(digitalRead(BUTTON_PIN_NEXT) == 0){
        delay(5);
      }
      cleanDis();
      ris(5, 5, numbers_one[mode]);
    }
    if (digitalRead(BUTTON_PIN_PREV) == 0){
      mode -= 1;
      mode = max(0, mode);
      while(digitalRead(BUTTON_PIN_PREV) == 0 ){
        delay(5);
      }
      cleanDis();
      ris(5, 5, numbers_one[mode]);
    }
    Serial.print("Mode = ");
    Serial.println(mode);
  }
  return mode;
}