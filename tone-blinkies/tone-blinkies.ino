void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  tone(9, 523, 1000); // play C5 (523 Hz) for 1sec async
  delay(2000); 
}
