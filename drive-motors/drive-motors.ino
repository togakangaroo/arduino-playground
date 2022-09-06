#define MOTOR1_ENA 3
#define MOTOR1_IN1 4
#define MOTOR1_IN2 5

bool clockwise = 0;

const int maxSpeed = 200;

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR1_ENA, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);

  delay(200);

  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
}

void loop() {
  analogWrite(MOTOR1_ENA, maxSpeed);
  if(clockwise) {
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
  } else {
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
  }

  delay(3000);

  for(int speed = maxSpeed; speed > 0; speed -= 10) {
    analogWrite(MOTOR1_ENA, speed);
    delay(100);
  }
  clockwise = !clockwise;
  Serial.println("swap");
}
