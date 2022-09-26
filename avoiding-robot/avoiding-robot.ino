struct UltrasonicSensorPins {
  int trigger;
  int echo;
};

const UltrasonicSensorPins ultrasonicSensors[1] = {{2, 3}};

struct MotorPins {
  int in1;
  int in2;
  int ena;
};

const MotorPins motors[2] = { {4, 5, 6}, {7, 8, 9}};

const int speakerPins[1] { 10 };

void stopMotor(MotorPins motor) {
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, LOW);
}

void turnMotorClockwise(MotorPins motor) {
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, HIGH);
}

void turnMotorCounterClockwise(MotorPins motor) {
  digitalWrite(motor.in1, HIGH);
  digitalWrite(motor.in2, LOW);
}

void setSpeed(int speed) {
  for(MotorPins motor : motors) {
    analogWrite(motor.ena, speed);
  }
}

void stop() {
  for(MotorPins motor : motors) {
    stopMotor(motor);
  }
}

void goForward() {
  for(MotorPins motor : motors) {
    turnMotorClockwise(motor);
  }
}

void goBackward() {
  for(MotorPins motor : motors) {
    turnMotorCounterClockwise(motor);
  }
}

void turnClockwise() {
  turnMotorCounterClockwise(motors[0]);
  turnMotorClockwise(motors[1]);
}

long readUltrasonicDistance(UltrasonicSensorPins ultrasonicSensor)
{
  pinMode(ultrasonicSensor.trigger, OUTPUT);  // Clear the trigger
  digitalWrite(ultrasonicSensor.trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicSensor.trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicSensor.trigger, LOW);
  pinMode(ultrasonicSensor.echo, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(ultrasonicSensor.echo, HIGH);
}

void setup() {

  for(MotorPins motor : motors) {
    pinMode(motor.ena, OUTPUT);
    pinMode(motor.in1, OUTPUT);
    pinMode(motor.in2, OUTPUT);
  }
  for(UltrasonicSensorPins ultrasonicSensor : ultrasonicSensors) {
    pinMode(ultrasonicSensor.trigger, OUTPUT);
    pinMode(ultrasonicSensor.echo, INPUT);
  }
  for(int speaker : speakerPins) {
    pinMode(speaker, OUTPUT);
  }

  setSpeed(150);
  turnClockwise();
}

void loop() {
  long closestDistance = 0xFFFF;
  for(UltrasonicSensorPins sensor : ultrasonicSensors) {
    long value = readUltrasonicDistance(sensor);
    if(value < closestDistance) {
      closestDistance = value;
    }
   }
}
