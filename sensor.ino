
int TURBINE;      //pengukuran SINYAL data yang bersifat incremental
int HSensor = 2; //nama alias pada pin 2
int Calc;
const int analogInPin = A0;
int buzz = 3;
int sensorValue = 0;
void speedrpm ()    //fungsi penghitungan dan interrupt
{
  TURBINE++; //bersifat incrementing (dengan mode falling edge)
}

void setup()
{
  pinMode(HSensor, INPUT); //inisialisasi sebagai input
  Serial.begin(9600);
  pinMode(A0, INPUT);
  attachInterrupt(0, speedrpm, RISING); //cara penulisan perintah interrupt
  pinMode(buzz, OUTPUT);
}

void loop ()
{

  sensorValue = analogRead(analogInPin);
  Serial.print("WLS = " );
  Serial.print(sensorValue * 100 / 1024);
  Serial.print("cm");
  TURBINE = 0; //data awal = 0
  sei(); //perintah aktifnya mode interrupt
  delay (1000); //nilai delay 1 detik
  cli(); //perintah untuk matinya program interrupt
  Calc = (TURBINE * 1 / 7.5); //Pulsa * 60 / 7.5

  //satuan FLOW RATE benda cair yaitu L / hour
  Serial.println("");
  Serial.print(  "WFS = " );
  Serial.print(Calc, DEC); //menampilkan hasil pembacaan kalkulasi flow rate dalam bentuk dec di serial monitor
  Serial.print(" L/m"); //Tampilkan L / hour pada baris baru

  if (sensorValue <= 2) {
    digitalWrite(buzz, LOW);
    Serial.println(" Status : AMAN");
  }
  if (sensorValue > 2 && sensorValue <= 3.5) {
    Serial.println(" Status : Siaga");
    digitalWrite(buzz, HIGH);
    delay(1000);
    digitalWrite(buzz, LOW);
    delay(1000);
  }
  if (sensorValue > 3.5) {
    Serial.println(" Status : Bahaya");
    digitalWrite(buzz, HIGH);
    delay(2000);
    digitalWrite(buzz, LOW);
    delay(2000);
  }
}
