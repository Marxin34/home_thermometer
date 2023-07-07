// home temp measurement MF
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <U8g2lib.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int T1 = 0;
int T2 = 0;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

unsigned long Time1 = 0;
unsigned long Time2 = 0;
#define czas_opoznienia1 5000
#define czas_opoznienia2 1000

void setup() {
  sensors.begin();
  u8g2.begin();
  pinMode(7, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(115200);
}
void loop() {
  // if (millis() >= Time2 + czas_opoznienia2) {
  //   Time2 += czas_opoznienia2;
  if (digitalRead(4) == LOW) {
    u8g2.setPowerSave(1);
  } else {
    u8g2.setPowerSave(0);
  }

  sensors.requestTemperatures();
  T1 = sensors.getTempCByIndex(0);
  T2 = sensors.getTempCByIndex(1);
  // }
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.setFontMode(1);
    u8g2.setCursor(0, 30);
    u8g2.print("T1-" + String(T1));
    u8g2.setCursor(0, 64);
    u8g2.print("T2-" + String(T2));

  } while (u8g2.nextPage());
  Serial.println("T1: " + String(T1));
  Serial.println("T2: " + String(T2));

  delay(1000);
  /*
    if (digitalRead(6) == HIGH) {
      if (millis() >= czas_opoznienia1 + Time1) {
        Time1 += czas_opoznienia1;
        digitalWrite(7, HIGH);
      }
    } else
      digitalWrite(7, LOW);
      */
}
