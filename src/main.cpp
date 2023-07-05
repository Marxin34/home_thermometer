//home temp measurement MF
#include <Arduino.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float T1 = 0;
float T2 = 0;

#define COLUMS 16
#define ROWS 2
#define LCD_SPACE_SYMBOL 0x20

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14,
                      POSITIVE);

unsigned long Time1 = 0;
unsigned long Time2 = 0;
#define czas_opoznienia1 5000
#define czas_opoznienia2 1000

void setup() {
  sensors.begin();
  lcd.begin(16, 2);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
}
void loop() {
  if (millis()>=Time2+czas_opoznienia2) {
    Time2 += czas_opoznienia2;
    sensors.requestTemperatures();
    T1 = sensors.getTempCByIndex(0);
    T2 = sensors.getTempCByIndex(1);
  }

  lcd.setCursor(0, 0);
  lcd.print(T1, 1);
  lcd.setCursor(4, 0);
  lcd.print(" na zewnatrz");
  lcd.setCursor(0, 1);
  lcd.print(T2, 1);
  lcd.setCursor(4, 1);
  lcd.print(" w srodku");

  if (digitalRead(6) == HIGH) {
    if (millis()>=czas_opoznienia1+Time1)
    {
      Time1+=czas_opoznienia1;
      digitalWrite(7, HIGH);
    }
  } else
    digitalWrite(7, LOW);
}
