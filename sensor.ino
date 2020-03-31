const int inoutansensor = A0;
int TURBINE;
int HSensor = 2;
int Calc;
int buzz = 3;

void speedrpm() {
  TURBINE++;
}

void setup() {
  pinMode(HSensor, INPUT);
  pinMode(inputsensor, INPUT);
  pinMode(buzz, OUTPUT);
  attachInterrupt(0, speedrpm, RISING);
  Serial.begin(9600);
  digitalWrite(buzz, LOW);
}

void loop() {
  int value = analogRead(inputsensor);

  float cm = (value * 4.0) / 600.0;
  int x = abs(cm);

  TURBINE = 0;
  sei();
  delay(1000);
  cli();
  Calc = (TURBINE * 1 / 7.5);

  Serial.print(Calc, DEC);
  Serial.print(" L/m ");
  Serial.print(cm);
  Serial.print(" cm");

  if ((Calc, DEC) < 1) {
    if (cm < 2) {
      Serial.print(" Status : 1");
    } else if (cm <= 3.5) {
      Serial.print(" Status : 2");
    } else {
      Serial.print(" Status : 2");
    }
  } else if ((Calc, DEC) < 2.5) {
    if (cm < 2) {
      Serial.print(" Status : 1");
    } else if (cm <= 3.5) {
      Serial.print(" Status : 2");
    } else {
      Serial.print(" Status : 3");
    }
  } else {
    if (cm < 2) {
      Serial.print(" Status : 1");
    } else if (cm <= 3.5) {
      Serial.print(" Status : 2");
    } else {
      Serial.print(" Status : 3");
    }
  }

  Serial.println("");
  delay(1000)
}
