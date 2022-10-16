#define MOTOR1 6
#define ULTRASONIC_ECHO 9
#define ULTRASONIC_TRIGGER 8

void setup() {
  pinMode(MOTOR1, OUTPUT);
  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Time to return is multipled by the wavelength of audible sound...or something like that?
  return 0.01725 * pulseIn(echoPin, HIGH);
}

void loop() {
  const long distance = readUltrasonicDistance(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);
  if(distance <= 0 || 2 <= distance)
    return;

  const float chanceOfEndingTheLoop = random(10, 50) / 100.0;
  while(random(100)/100.0 > chanceOfEndingTheLoop) {
    analogWrite(MOTOR1, random(150, 255));
    delay(random(1000, 3000));
  }

  digitalWrite(MOTOR1, LOW);
  delay(2000);
}
