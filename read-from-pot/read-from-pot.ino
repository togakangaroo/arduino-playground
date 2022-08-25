int potentiometerValue = 500;

void setup()
{
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  potentiometerValue = analogRead(A1);
  digitalWrite(9, HIGH);
  Serial.println(potentiometerValue);
  delay(potentiometerValue); // Wait for potentiometerValue millisecond(s)
  digitalWrite(9, LOW);
  delay(potentiometerValue); // Wait for potentiometerValue millisecond(s)
}
