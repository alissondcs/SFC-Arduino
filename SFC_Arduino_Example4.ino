// list variables according to number of steps
bool step_00 = 1;
bool step_01 = 0;
bool step_02 = 0;
bool step_03 = 0;

void setup() {
  // define inputs and outputs used
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // perform input readings
  bool i2 = !digitalRead(2);
  bool i3 = !digitalRead(3);
  bool i4 = !digitalRead(4);
  bool i5 = !digitalRead(5);
  bool i6 = !digitalRead(6);

  //implement activation and deactivation functions of each step of the SFC
  if (step_03 && i6) {
    step_00 = 1;
  }
  else if (step_01) {
    step_00 = 0;
  }

  if ((step_00 && i2) || (step_02 && i5)) {
    step_01 = 1;
  }
  else if (step_02) {
    step_01 = 0;
  }

  if (step_01 && i3) {
    step_02 = 1;
  }
  else if (step_03 || step_01) {
    step_02 = 0;
  }

  if (step_02 && i4) {
    step_03 = 1;
  }
  else if (step_00) {
    step_03 = 0;
  }

  Serial.print("step_00 state: ");
  Serial.println(step_00);
  Serial.print("step_01 state: ");
  Serial.println(step_01);
  Serial.print("step_02 state: ");
  Serial.println(step_02);
  Serial.print("step_03 state: ");
  Serial.println(step_03);

  // switch outputs according to the actions associated with each step
  digitalWrite(8, (step_01 || step_02));
  digitalWrite(9, step_02);
  digitalWrite(10, step_03);

  delay (1000);
}
