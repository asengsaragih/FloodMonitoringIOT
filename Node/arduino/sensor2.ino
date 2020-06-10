/*
   Sensor water level di ganti jadi A1
   Sensor water flow di posisi 2
*/

const int inputsensor = A1;
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

  //  Serial.print(Calc, DEC);
  //  Serial.print(" L/m ");
  //  Serial.print(cm);
  //  Serial.print(" cm");

  Serial.print(Calc, DEC);
  Serial.print(",");
  Serial.print(cm);
  Serial.print(",");

  if ((Calc, DEC) < 1) {
    if (cm < 2) {
      Serial.print("1");
    } else if (cm <= 3.5) {
      Serial.print("2");
    } else {
      Serial.print("2");
    }
  } else if ((Calc, DEC) < 2.5) {
    if (cm < 2) {
      Serial.print("1");
    } else if (cm <= 3.5) {
      Serial.print("2");
    } else {
      Serial.print("3");
    }
  } else {
    if (cm < 2) {
      Serial.print("1");
    } else if (cm <= 3.5) {
      Serial.print("2");
    } else {
      Serial.print("3");
    }
  }

  Serial.println("");
  delay(1000);
}
