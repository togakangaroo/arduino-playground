unsigned int time=0;

struct LightState {
  bool isOn;
};

LightState state[2] {{ 1 }, { 0 }};

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  TCCR0A = (1 << WGM01); //CTC mode
  OCR0A = 250; //This sets resulution to 1ms for some reason

  TIMSK0 |= (1 << OCIE0A); //set interrupt request
  sei(); //enable interrupt

  // prescale 1/64 clock? what's that?
  TCCR0B |= (1 << CS01);
  TCCR0B |= (1 << CS00);
}

void loop() {
  // On and off every other third of a second
  state[0] = { ((time / (1*333)) % 2) };

  // On and off every 3/5ths second
  state[1] = { ((time / (3*200)) % 2) };

  digitalWrite(4, state[0].isOn);
  digitalWrite(3, state[1].isOn);
}

ISR(TIMER0_COMPA_vect) { // interrupt request
  if(time == 0xFFFF) {
    time = 0;
  } else {
    time++;
  }
}
