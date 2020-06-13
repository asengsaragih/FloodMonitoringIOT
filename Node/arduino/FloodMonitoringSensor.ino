
int TURBINE;      //pengukuran SINYAL data yang bersifat incremental
int HSensor = 2; //nama alias pada pin 2
float Calc;
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
  TURBINE = 0; //data awal = 0
  sei(); //perintah aktifnya mode interrupt
  delay (1000); //nilai delay 1 detik
  cli(); //perintah untuk matinya program interrupt
  Calc = (TURBINE * 1.0 / 7.5); //Pulsa * 60 / 7.5
  //satuan FLOW RATE benda cair yaitu L / hour
  sensorValue = analogRead(analogInPin);
  float level = sensorValue * 4.0 / 1024;
  Serial.print(level);
  Serial.print(",");
  Serial.print(Calc); //menampilkan hasil pembacaan kalkulasi flow rate dalam bentuk dec di serial monitor
  Serial.print(",");
  if (Calc < 1) {
    if (level < 2) {
      Serial.print(1);
    } else if (level <= 3.5) {
      Serial.print(2);
    } else {
      Serial.print(2);
    }
  } else if (Calc < 2.5) {
    if (level < 2) {
      Serial.print(1);
    } else if (level <= 3.5) {
      Serial.print(2);
    } else {
      Serial.print(3);
    }
  } else {
    if (level < 2) {
      Serial.print(1);
    } else if (level <= 3.5) {
      Serial.print(2);
    } else {
      Serial.print(3);
    }
  }
  
  Serial.println("");
}
