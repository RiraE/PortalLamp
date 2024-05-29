// бот отправляет обратно сообщения из любого чата (эхо-бот)
#define LED_PIN D6   // пин ленты
#define NUMLEDS 60      // кол-во светодиодов
//#define BRIGHTNESS 50
#include "FastLED.h" 
//#include "pitches.h"


CRGB leds[NUMLEDS];

uint8_t current_brightness = 50;

#define WIFI_SSID "TP-Link_2F2D"
#define WIFI_PASS "70345896"
#define BOT_TOKEN "****"
#define ChatID "805575536"
#include <ESP8266WiFi.h>
#include <FastBot.h>
FastBot bot(BOT_TOKEN);


void show_opposite_color(uint8_t r, uint8_t g, uint8_t b) {
  fill_solid(leds, NUMLEDS, CRGB(255- r, 255 - g, 255 - b));
  FastLED.show();
  delay(500);
}

void clock(unsigned long time) {
  uint32_t tmr1;
  int8_t diode = NUMLEDS - 1;

  while (diode >= 0) {
    if ((millis() - tmr1) >= (time / NUMLEDS)) {
            Serial.println(diode);
      leds[diode] =  CRGB::Black;
      diode--;
      FastLED.show();
      yield();
      tmr1 = millis();
    }

    if (diode == ((NUMLEDS + NUMLEDS % 2) / 2  + _max(40000/time, 1)) || diode == 6 || diode == 4 || diode == 2) {
      FastLED.setBrightness(255);
      FastLED.show();
    }

    if (diode == ((NUMLEDS + NUMLEDS % 2) / 2 - _max(40000/time, 1)) || diode == 5 || diode == 3) {
      FastLED.setBrightness(current_brightness);
      FastLED.show();
    }
  }
}

//void alarm() {
  //Still alive for later

  //pinMode(D5, OUTPUT); 
  //digitalWrite(D5, HIGH);

  //double duration = 1;
  //for (int i = 0; duration > 0.0; i += 2)
  //{
  //  int note = song[i];
  //  duration = song[i + 1];

  // int noteDuration = (1600.0 * (duration / 4));
  //  tone(8, note, noteDuration);

  //  int pauseBetweenNotes = noteDuration * 1.3;
  //  delay(pauseBetweenNotes);
  //  noTone(8);
  //}
//}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUMLEDS);

  connectWiFi();
  bot.attach(newMsg);


}

void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  Serial.print(msg.chatID);     // ID чата 
  Serial.print(", ");
  Serial.print(msg.username);   // логин
  Serial.print(", ");
  Serial.println(msg.text);     // текст
}

void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}
