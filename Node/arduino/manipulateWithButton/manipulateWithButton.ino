#define NORMAL_BTN 5
#define WASPADA_BTN 6
#define BAHAYA_BTN 7

int category = 1;
float debit;
float level;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  btnConf();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(NORMAL_BTN) == LOW) {
//    Serial.println("NORMAL");
    category = 1;
  }

  if (digitalRead(WASPADA_BTN) == LOW) {
//    Serial.println("WASPADA");
    category = 2;
  }

  if (digitalRead(BAHAYA_BTN) == LOW) {
//    Serial.println("BAHAYA");
    category = 3;
  }

  if(category == 1) {
    debit = random(55, 60)  / 100.0;
    level = random(85, 90)  / 100.0;
  } else if(category == 2) {
    debit = random(255, 260)  / 100.0;
    level = random(270, 275)  / 100.0;
  } else {
    debit = random(380, 385)  / 100.0;
    level = random(360, 364)  / 100.0;
  }

  Serial.print(debit);
  Serial.print(",");
  Serial.print(level);
  Serial.print(",");
  Serial.print(category);
  Serial.println();

  delay(1000);
}

void btnConf() {
  pinMode(NORMAL_BTN, INPUT);
  pinMode(WASPADA_BTN, INPUT);
  pinMode(BAHAYA_BTN, INPUT);

  digitalWrite(NORMAL_BTN, HIGH);
  digitalWrite(WASPADA_BTN, HIGH);
  digitalWrite(BAHAYA_BTN, HIGH);
}
