/*
 * Program Proyek Akhir Manipulasi
 *
 * Tinggal ganti angka di variable category
 * 1 = aman
 * 2 = siaga
 * 3 = waspada
*/

long second = 1000;
long minute = second * 60;
long hour = minute * 60;

int category = 1;
float debit;
float level;

int buttonDanger = 4;
int buttonStandby = 5;
int buttonNormal = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Button  
  pinMode(buttonDanger, INPUT);
  pinMode(buttonStandby, INPUT);
  pinMode(buttonNormal, INPUT);
  
  digitalWrite(buttonDanger, HIGH);
  digitalWrite(buttonStandby, HIGH);
  digitalWrite(buttonNormal, HIGH);
}

void loop() {
  if (digitalRead(buttonDanger) == LOW) {
    category = 3;
  }

  if (digitalRead(buttonStandby) == LOW) {
    category = 2;
  }

  if (digitalRead(buttonNormal) == LOW) {
    category = 1;
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

  /*
  * waktunya tinggal diganti sesuai dengan keinginan
  * jika mau 15 menit delay(minute * 15); dan seterusnya
  */

  delay(second);
}
