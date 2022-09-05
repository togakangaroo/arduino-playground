#define MOTOR1_ENA 3
#define MOTOR1_IN1 4
#define MOTOR1_IN2 5

bool clockwise = 0;

void setup() {
  pinMode(MOTOR1_ENA, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);

  delay(200);

  analogWrite(MOTOR1_ENA, 50);
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
}

void loop() {
  if(clockwise) {
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
  } else {
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
  }

  delay(3000);
  clockwise = !clockwise;
}
