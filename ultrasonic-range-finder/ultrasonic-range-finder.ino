int distance = 0;
const int lightPin = 6;
const int speakerPin = 8;

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
  Serial.print("2 Blinky: ");
  Serial.println(distance);
  if(distance < 30) {
    tone(speakerPin, 523);
  } else {
    noTone(speakerPin);
  }
  long blinkDuration = distance * 6;
  if(blinkDuration > 759) {
    blinkDuration = 759;
  }
  digitalWrite(lightPin, HIGH);
  delay(blinkDuration);
  digitalWrite(lightPin, LOW);
  delay(blinkDuration);
}
