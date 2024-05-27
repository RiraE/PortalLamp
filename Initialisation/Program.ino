void show_color(uint8_t r, uint8_t g, uint8_t b, uint8_t start = 0, uint8_t end = NUMLEDS) {
  strip.fill(start, end - 1, mRGB(r, g, b));
  first_diode[0], first_diode[1], first_diode[2] = r, g, b;
  strip.show();
  delay(40);
}

void show_opposite_color(uint8_t r, uint8_t g, uint8_t b, uint8_t start = 0, uint8_t end = NUMLEDS) {
  strip.fill(start, end-1, mRGB(255- r, 255 - g, 255 - b));
  first_diode[0], first_diode[1], first_diode[2] = 255 - r, 255 - g, 255 - b;
  strip.show();
  delay(40);
}

void clock(unsigned long time) {
  uint32_t tmr1;
  int8_t diode = NUMLEDS - 1;

  while (diode >= 0) {
    if ((millis() - tmr1) >= (time / NUMLEDS)) {
      show_color(first_diode[0], first_diode[1], first_diode[2], 0, NUMLEDS - diode);
      Serial.println(diode);
      diode--;
      strip.show();
      tmr1 = millis();
    }

    if (diode == ((NUMLEDS + NUMLEDS % 2) / 2  + max(40000/time, 1)) || diode == 6 || diode == 4 || diode == 2) {
      strip.setBrightness(255);
      strip.show();
    }

    if (diode == ((NUMLEDS + NUMLEDS % 2) / 2 - max(40000/time, 1)) || diode == 5 || diode == 3) {
      strip.setBrightness(first_diode[3]);
      strip.show();
    }
  }
  Serial.println("here!");
}

void setup() {
  strip.clear();
  Serial.begin(9600);
  first_diode[3] = 150;
  strip.setBrightness(first_diode[3]);
  
  //Однотонная заливка в один цвет

  show_color(186, 21, 232);
  delay(100);
  //Однотонная заливка в противоположный данному цвет

  clock(60000);

  show_color(255, 69, 0);
}


void alarm() {

}

void loop() {
}