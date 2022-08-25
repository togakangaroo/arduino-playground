const int trigPin = 10;
const int echoPin = 9;
// defines variables
long duration;
int distance;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  long blinkDuration = distance * 4;
  if(blinkDuration > 759) {
    blinkDuration = 759;
  }

  Serial.print("Blinky: ");
  Serial.println(blinkDuration);
  digitalWrite(6, HIGH);
  delay(blinkDuration);
  digitalWrite(6, LOW);
  delay(blinkDuration);

}
