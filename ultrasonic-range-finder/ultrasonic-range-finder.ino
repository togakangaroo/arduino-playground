struct RangePlayer {
  int triggerPin;
  int echoPin;
  int speakerPin;
  int minDistance;
  int maxDistance;
  int frequencyMultiplier;
};

RangePlayer players[2] {
  {  7,  9,  5,  0, 40, 25  },
  { 10, 14, 18,  9, 60, 15 }};

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
  for(RangePlayer player : players) {
    pinMode(player.triggerPin, OUTPUT);
    pinMode(player.echoPin, INPUT);
    pinMode(player.speakerPin, OUTPUT);
  }
}

void loop()
{
  Serial.println("3 Blinky: ");
  for(RangePlayer player : players) {
    int distance = 0.01723 * readUltrasonicDistance(player.triggerPin, player.echoPin);
    Serial.println(distance);
    if(player.minDistance < distance && distance < player.maxDistance) {
      int frequency = distance*player.frequencyMultiplier;
      tone(player.speakerPin, frequency);
    } else {
      noTone(player.speakerPin);
    }
  }
  delay(100);
}
