#include <IRremote.h>
#include <FastLED.h>

// For IR remote (shark)
#define IR_0 0xFF4AB5
#define IR_1 0xFF6897
#define IR_2 0xFF9867
#define IR_3 0xFFB04F
#define IR_4 0xFF30CF
#define IR_5 0xFF18E7
#define IR_6 0xFF7A85
#define IR_7 0xFF10EF
#define IR_8 0xFF38C7
#define IR_9 0xFF5AA5
#define IR_UP 0xFF629D
#define IR_DOWN 0xFFA857
#define IR_RIGHT 0xFFC23D
#define IR_LEFT 0xFF22DD
#define IR_OK 0xFF02FD

#define IR_PIN 11
IRrecv ir_receiver(IR_PIN);
decode_results ir_results;

// FOR LED lights
#define LED_PIN 12
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

enum STATE{
  OFF,
  GR_FLASH,
  BW_FLASH,
  CANE,
} state = OFF;

const byte led_grid[5][10] = {
  { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9},
  {19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
  {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
  {39, 38, 37, 36, 35, 34, 33, 32, 31, 30},
  {40, 41, 42, 43, 44, 45, 46, 47, 48, 49}
};

void setup() {
  ir_receiver.enableIRIn();
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Ready");
}

void check_ir() {
 while (!ir_receiver.isIdle()); // Wait until not busy
  if (ir_receiver.decode(&ir_results)) {
    switch (ir_results.value) {
      case IR_0:
        state = OFF;
        Serial.println("Off!");
        break;
      case IR_1:
        state = GR_FLASH;
        Serial.println("Flashing green and red!");
        break;
      case IR_2:
        state = BW_FLASH;
        Serial.println("Flashing blue and white!");
        break;
      case IR_3:
        state = CANE;
        Serial.println("Candy cane!");
        break;
    }
    ir_receiver.resume();
  }
}

void check_serial() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case '0':
        state = OFF;
        Serial.println("Off!");
        break;
      case '1':
        state = GR_FLASH;
        Serial.println("Flashing green and red!");
        break;
      case '2':
        state = BW_FLASH;
        Serial.println("Flashing blue and white!");
        break;
      case '3':
        state = CANE;
        Serial.println("Candy cane!");
        break;
    }
  }
}

void smart_delay(unsigned long t) {
  const unsigned long stop_time = millis() + t;
  STATE start_state = state;
  while (millis() < stop_time && state == start_state) {
    check_ir();
    check_serial();
    delay(1);
  }
}

void loop() {
  smart_delay(1);

  // Off state
  while (state == OFF) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    smart_delay(100);
  }

  // Green and red flashing state
  int grDelay = 250;
  while (state == GR_FLASH){
    for (int i = 0; i < NUM_LEDS; i ++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(64, 0, 0);
      } else {
        leds[i] = CRGB(0, 64, 0);
      }
    }
    FastLED.show();
    smart_delay(grDelay);

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(0, 64, 0);
      } else {
        leds[i] = CRGB(64, 0, 0);
      }
    }
    FastLED.show();
    smart_delay(grDelay);
  }
  
  // Blue and white flashing state
  int bwDelay = 100;
  while (state == BW_FLASH){
    for (int i = 0; i < NUM_LEDS; i ++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(0, 0, 64);
      } else {
        leds[i] = CRGB(21, 21, 22);
      }
    }
    FastLED.show();
    smart_delay(bwDelay);

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(21, 21, 22);
      } else {
        leds[i] = CRGB(0, 0, 64);
      }
    }
    FastLED.show();
    smart_delay(bwDelay);
  }
  
  // Candy canse state (red and white flashing)
  int caneDelay = 500;
  while (state == CANE){
    for (int i = 0; i < NUM_LEDS; i ++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(64, 0, 0);
      } else {
        leds[i] = CRGB(22, 21, 21);
      }
    }
    FastLED.show();
    smart_delay(caneDelay);

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(22, 21, 21);
      } else {
        leds[i] = CRGB(64, 0, 0);
      }
    }
    FastLED.show();
    smart_delay(caneDelay);
  }

}
