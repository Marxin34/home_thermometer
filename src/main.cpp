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
int power_save = 1;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

unsigned long time_of_bt_press = 0;
unsigned delay_time = 10000;

void setup() {
  sensors.begin();
  u8g2.begin();
  pinMode(4, INPUT_PULLUP);
  Serial.begin(115200);
}
void loop() {
  int button_state = digitalRead(4);

  if (button_state == LOW && power_save == 1) {
    power_save = 0;
    time_of_bt_press = millis() + delay_time;
    Serial.println("Display ON" + String(millis()) + " " + String(power_save));
  }
  if (power_save == 0) {
    if (millis() >= time_of_bt_press) {
      power_save = 1;
      Serial.println("Display OFF" + String(millis()) + " " +
                     String(power_save));
    }
  }

  sensors.requestTemperatures();
  T1 = sensors.getTempCByIndex(0);
  T2 = sensors.getTempCByIndex(1);

  u8g2.setPowerSave(power_save);
  u8g2.firstPage();
  do {
    u8g2.setContrast(255);
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.setFontMode(1);
    u8g2.setCursor(0, 30);
    u8g2.print("TZ: " + String(T1));
    u8g2.setCursor(0, 64);
    u8g2.print("TW: " + String(T2));
  } while (u8g2.nextPage());
  delay(50);
}
