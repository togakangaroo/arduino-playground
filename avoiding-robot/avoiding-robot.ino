struct UltrasonicSensorPins {
  int trigger;
  int echo;
};

const UltrasonicSensorPins ultrasonicSensors[1] = {{10, 11}};

struct MotorPins {
  int in1;
  int in2;
  int ena;
};

const MotorPins motors[2] = { {4, 5, 6}, {7, 8, 9}};

const int speakerPins[1] { 13 };

int consequitiveTimesDistanceUnderThreshold = 0;

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
  digitalWrite(ultrasonicSensor.trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicSensor.trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicSensor.trigger, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  long echoBack = pulseIn(ultrasonicSensor.echo, HIGH);
  return echoBack * 0.01723;
}

void setup() {

  Serial.begin(9600);

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
  bool shouldBackOut = false;
  long closestDistance = 0xFFFF;
  for(UltrasonicSensorPins sensor : ultrasonicSensors) {
    long value = readUltrasonicDistance(sensor);
    Serial.println(value);
    if(0 < closestDistance && value < closestDistance) {
      closestDistance = value;
    }
   }
  consequitiveTimesDistanceUnderThreshold += (0 < closestDistance && closestDistance < 30) ? 1 : 0;
  
  if(consequitiveTimesDistanceUnderThreshold >= 2) {
    consequitiveTimesDistanceUnderThreshold = 0;
    shouldBackOut = true;
  }

  if(shouldBackOut) {
    for(int speaker : speakerPins) {
      tone(speaker, 500);
    }
    goBackward();
    delayMicroseconds(1000);
    turnClockwise();
    delayMicroseconds(800);
    goBackward();
  } else {
    for(int speaker : speakerPins) {
      noTone(speaker);
    }
    goForward();
  }
}
