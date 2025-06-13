//  temperature & lux
#define TMP36_INPUT 0
#define CDS_INPUT 1
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F,16,2); 
void setup() {
  Serial.begin(9600);
  lcd.init(); // LCD 설정
  lcd.clear();      // LCD를 모두 지운다.
  lcd.backlight();  // 백라이트를 켠다.
  lcd.setCursor(0,0);
  lcd.print("AR06_Exam");
  delay(3000);

}

void loop() {
  // Temperature from TMP36
  int temp_value = analogRead(TMP36_INPUT);
  // converting that reading to voltage
  float voltage = temp_value * 5.0 * 1000;  // in mV
  voltage /= 1023.0;
  float tempC = (voltage - 500) / 10 ;

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
  lcd.print("lux : "+ lux);
  lcd.setCursor(0,1);
  lcd.println("tmp : tempC");
  delay(1000);


}

//Voltage to Lux
double luminosity (int RawADC0){
  double Vout=RawADC0*5.0/1023.0;  // 5/1023 (Vin = 5 V)
  double lux=(2500/Vout-500)/10.0;  
  // lux = 500 / Rldr, Vout = Ildr*Rldr = (5/(10 + Rldr))*Rldr
  return lux;
}


