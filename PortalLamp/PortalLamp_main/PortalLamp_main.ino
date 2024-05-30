// бот отправляет обратно сообщения из любого чата (эхо-бот)
#define LED_PIN D6   // пин ленты
#define NUMLEDS 60      // кол-во светодиодов
//#define BRIGHTNESS 50
#include "FastLED.h" 
#include "pitches.h"


CRGB leds[NUMLEDS];

uint8_t current_brightness = 50;

#define WIFI_SSID "TP-Link_2F2D"
#define WIFI_PASS "70345896"
#define BOT_TOKEN "***"
#define ChatID "805575536"
#include <ESP8266WiFi.h>
#include <FastBot.h>
FastBot bot(BOT_TOKEN);

bool set_timer = 0;
bool set_brightness = 0;

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

  for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(D1, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
  fill_solid(leds, NUMLEDS, CRGB(255, 30, 0)); //поменять на цвет, который был до выключения
  FastLED.show();
}

void alarm() {
  //Still alive 

  pinMode(D1, OUTPUT); 
  digitalWrite(D5, HIGH);

  double duration = 1;
  for (int i = 0; duration > 0.0; i += 2)
  {
    int note = song[i];
    duration = song[i + 1];

   int noteDuration = (1600.0 * (duration / 4));
    tone(D1, note, noteDuration);

    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUMLEDS);
  FastLED.setBrightness(current_brightness);
  FastLED.clearData();
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

  if (msg.text == "/start") {
    bot.sendMessage("Привет! Я тут :) Чтобы начать работу, табни кнопку Menu", msg.chatID);
  }

  else if (msg.text == "/ledon") {
    fill_solid(leds, NUMLEDS, CRGB(255, 30, 0));
    FastLED.show();
  }

  else if (msg.text == "/brightness") {
    bot.sendMessage("Пожалуйста, введи яркость, которую хочешь получить (от 0 до 255). Текущая яркость: " + String(current_brightness) + ". Если передумаешь - просто нажми любую другую команду!", msg.chatID);
    set_brightness = 1;
  }

  else if (msg.text == "/ledoff") {
    FastLED.clearData();
    FastLED.show();
  }

  else if (msg.text == "/melody") {
    alarm();
  }

  else if (msg.text == "/settimer") {
    bot.sendMessage("Пожалуйста, введи время, которое нужно засечь, в формате ЧЧ,ММ,СС. Если передумаешь - просто нажми любую другую команду!", msg.chatID);
    set_timer = 1;
    Serial.println(set_timer);
  }

  else if (set_timer && msg.text[2]==',') {
     clock(msg.text.substring(0, 2).toInt() * 3600000 + msg.text.substring(3, 5).toInt() * 60000 + msg.text.substring(6, 8).toInt() * 1000);
     set_timer = 0;
  }

  else if (set_brightness && isdigit(msg.text[0])) {
      current_brightness = _min(msg.text.toInt(), 255);
      FastLED.setBrightness(current_brightness);
      FastLED.show();
      set_brightness = 0;
  }

  else {
    bot.sendMessage("If there's something strage in your neighborhood, who you're gonna call? This profile!", msg.chatID);
  }
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
  bot.sendMessage("Все подключено и работает!", ChatID);
}
