#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Solar Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawValue = analogRead(A0);

  float voltage = rawValue * (5.0 / 1023.0) * 4.0;
  float power = (voltage * voltage) / 10.0;

  lcd.setCursor(0, 0);
  lcd.print("V: ");
  lcd.print(voltage, 2);
  lcd.print(" V    ");

  lcd.setCursor(0, 1);
  lcd.print("P: ");
  lcd.print(power, 2);
  lcd.print(" W    ");

  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | ");

  Serial.print("Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  delay(1000);
}