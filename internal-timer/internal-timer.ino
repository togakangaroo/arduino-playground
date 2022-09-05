unsigned int time=0;

struct LightState {
  bool isOn;
};

struct SpeakerState {
  int frequency;
};

struct State {
  LightState lights[2];
  SpeakerState speakers[1];
};
State state {{{ 1 }, { 0 }}, {{ 22 }} };

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  TCCR0A = (1 << WGM01); //CTC mode
  OCR0A = 125; //This sets resulution to .5ms for some reason

  TIMSK0 |= (1 << OCIE0A); //set interrupt request
  sei(); //enable interrupt

  // prescale 1/64 clock? what's that?
  TCCR0B |= (1 << CS01);
  TCCR0B |= (1 << CS00);
}

void loop() {
  // On and off every other third of a second
  state.lights[0] = { ((time / (1*333)) % 2) };

  // On and off every 3/5ths second
  state.lights[1] = { ((time / (3*200)) % 2) };

  const int speakerState = { ((time / (2)) % (2000/state.speakers[0].frequency)) };

  digitalWrite(4, state.lights[0].isOn);
  digitalWrite(3, state.lights[1].isOn);
  digitalWrite(5, speakerState);
}


ISR(TIMER0_COMPA_vect) { // interrupt request
  if(time == 0xFFFF) {
    time = 0;
  } else {
    time++;
  }
}
