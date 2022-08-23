const int ULTRASONIC_TRIG = 7;
const int ULTRASONIC_ECHO = 8;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  long distance = readUltrasonicDistance(ULTRASONIC_TRIG, ULTRASONIC_ECHO);
  Serial.println(distance);
  delay(500); 
}
