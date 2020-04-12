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
 
int category = 3;
float debit;
float level;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  
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


  Serial.print("Debit : ");
  Serial.print(debit);
  Serial.print(" L/m Level : ");
  Serial.print(level);
  Serial.print(" cm Category : ");
  Serial.print(category);
  Serial.println();

  /*
  * waktunya tinggal diganti sesuai dengan keinginan
  * jika mau 15 menit delay(minute * 15); dan seterusnya
  */
  
  delay(second);
}