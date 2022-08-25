const int LIGHT_BLINKING_PIN

int counter = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(LIGHT_BLINKING_PIN, OUTPUT);
}

void loop()
{
  counter = counter + 1;

  Serial.println(counter);

  digitalWrite(LIGHT_BLINKING_PIN, HIGH);
  delay(200);
  digitalWrite(LIGHT_BLINKING_PIN, LOW);
  delay(400);
  digitalWrite(LIGHT_BLINKING_PIN, HIGH);
  delay(400);
  digitalWrite(LIGHT_BLINKING_PIN, LOW);
  delay(200);
}
