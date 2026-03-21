void vivodTCRT(int number){
  Serial.print("Tcrt1: ");
  Serial.print(analogRead(TCRT1));
  Serial.print(" Tcrt2: ");
  Serial.print(analogRead(TCRT2));
  Serial.print(" ");
  Serial.println(number);
}