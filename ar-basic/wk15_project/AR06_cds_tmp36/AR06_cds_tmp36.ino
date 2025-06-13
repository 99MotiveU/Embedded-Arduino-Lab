//  temperature & lux
#define TMP36_INPUT 0
#define CDS_INPUT 1
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
const int ledR = 2;
const int ledY = 3;
int buzzerPin = 9;
int tempo = 200;
const int ledB = 4;
void setup() {
  Serial.begin(9600);
  lcd.init(); // LCD 설정
  lcd.clear();      // LCD를 모두 지운다.
  lcd.backlight();  // 백라이트를 켠다.
  lcd.setCursor(0,0);
  lcd.print("AR06_Exam");
  delay(3000);

  pinMode(ledB,OUTPUT);
  pinMode(ledR,OUTPUT);
  pinMode(ledY,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Temperature from TMP36
  int temp_value = analogRead(TMP36_INPUT);
  // converting that reading to voltage
  float voltage = temp_value * 5.0 * 1000;  // in mV
  voltage /= 1023.0;
  float tempC = (voltage - 500) /0 ;

  delay(250);
  // Lux from CdS (LDR)
  int cds_value = analogRead(CDS_INPUT);
  int lux = int(luminosity(cds_value));
  Serial.print("AR06,");
  Serial.print(tempC);
  Serial.print(",");
  Serial.println(lux);
  
  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("lux : ");
  lcd.print(lux);
  lcd.setCursor(0,1);
  lcd.print("tmp : ");
  lcd.print(tempC);

  //온도가 40도 미만일때 노란 led가 켜지고 이상일땐 빨간 led가 켜진다.
  if(tempC<40){
    digitalWrite(ledY,HIGH);
    digitalWrite(ledR,LOW);
  }else{
    digitalWrite(ledY,LOW);
    digitalWrite(ledR,HIGH);
  }
  // 온도가 18도 이상 일때 부저 울린다.
  if(18<tempC){
  frequency(262);
  }else
   noTone(buzzerPin);
   //lux값이 0에서 100사이 일때 파란 led가 켜진다
 if(0<lux<100){
  digitalWrite(ledB,HIGH);
 }else{
   digitalWrite(ledB,LOW);
 }
 }

//Voltage to Lux
double luminosity (int RawADC0){
  double Vout=RawADC0*5.0/1023.0;  // 5/1023 (Vin = 5 V)
  double lux=(2500/Vout-500)/1.0;  
  // lux = 500 / Rldr, Vout = Ildr*Rldr = (5/(10 + Rldr))*Rldr
  return lux;
}

void frequency(int freq)
{
  // 주파수 값을 받아 부저를 울리는 함수

  tone(buzzerPin, freq, tempo);
}

