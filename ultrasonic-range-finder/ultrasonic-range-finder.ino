int distance = 0;
int lightPin = 6;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);  // Clear the trigger
  pinMode(9, INPUT);
}

void loop()
{
  distance = 0.01723 * readUltrasonicDistance(10, 9);
  Serial.print("1 Blinky: ");
  long blinkDuration = distance * 6;
  if(blinkDuration > 759) {
    blinkDuration = 759;
  }
  Serial.println(blinkDuration);
  digitalWrite(6, HIGH);
  delay(blinkDuration);
  digitalWrite(6, LOW);
  delay(blinkDuration);
}
