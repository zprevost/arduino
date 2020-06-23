#include <IRremote.h>
#include <FastLED.h>

// For thermometer
#define TEMP_PIN 0

// For IR remote
#define IR_KEY_0 16738455
#define IR_KEY_1 16724175
#define IR_KEY_2 16718055
#define IR_KEY_3 16743045
#define IR_KEY_4 16716015
#define IR_KEY_5 16726215
#define IR_KEY_6 16734885
#define IR_KEY_7 16728765
#define IR_KEY_8 16730805
#define IR_KEY_9 16732845
#define IR_KEY_ON_OFF 16753245
#define IR_KEY_VOL_UP 16736925
#define IR_KEY_VOL_DOWN 16754775
#define IR_KEY_FORWARD 16761405
#define IR_KEY_REVERSE 16720605

// For IR remote
#define IR_PIN 11
IRrecv ir_receiver(IR_PIN);
decode_results ir_results;

// FOR LED lights
#define LED_PIN 12
#define NUM_LEDS 48
CRGB leds[NUM_LEDS];
byte hue = 125;
byte sat = 255;
byte val = 255;

enum STATE {
  OFF,
  ON,
  COLOR,
  RANDOM,
  MOVE,
  TEMP,
  XMAS,
} state = OFF;

void setup() {
  ir_receiver.enableIRIn();
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  Serial.println("Ready");
}

void check_ir() {
  while (!ir_receiver.isIdle()); // Wait until not busy
  if (ir_receiver.decode(&ir_results)) {
    //Serial.println(ir_results.value);
    switch (ir_results.value) {

      case IR_KEY_0:
        state = OFF;
        Serial.println("OFF");
        break;
      case IR_KEY_1:
        state = ON;
        Serial.println("ON");
        break;
      case IR_KEY_2:
        state = COLOR;
        Serial.println("COLOR");
        break;
      case IR_KEY_3:
        state = RANDOM;
        Serial.println("RANDOM");
        break;
      case IR_KEY_4:
        state = MOVE;
        Serial.println("MOVE");
        break;
      case IR_KEY_5:
        state = TEMP;
        Serial.println("TEMP");
        break;
      case IR_KEY_6:
        state = XMAS;
        Serial.println("XMAS");
        break;

      case IR_KEY_VOL_UP:
        val = min(val + 16, 255);
        Serial.print("Val up to ");
        Serial.println(val);
        break;
      case IR_KEY_VOL_DOWN:
        val = max(val - 16, 0);
        Serial.print("Val down to ");
        Serial.println(val);
        break;
      case IR_KEY_FORWARD:
        hue = (256 + hue + 16) % 256;
        Serial.print("Hue up to ");
        Serial.println(hue);
        break;
      case IR_KEY_REVERSE:
        hue = (256 + hue - 16) % 256;
        Serial.print("Hue down to ");
        Serial.println(hue);
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
        Serial.println("OFF");
        break;
      case '1':
        state = ON;
        Serial.println("ON");
        break;
      case '2':
        state = COLOR;
        Serial.println("COLOR");
        break;
      case '3':
        state = RANDOM;
        Serial.println("RANDOM");
        break;
      case '4':
        state = MOVE;
        Serial.println("MOVE");
        break;
      case '5':
        state = TEMP;
        Serial.println("TEMP");
        break;
      case '6':
        state = XMAS;
        Serial.println("XMAS");
        break;

      case 'w':
        val = min(val + 16, 255);
        Serial.print("Val up to ");
        Serial.println(val);
        break;
      case 's':
        val = max(val - 16, 0);
        Serial.print("Val down to ");
        Serial.println(val);
        break;
      case 'a':
        hue = (256 + hue + 16) % 256;
        Serial.print("Hue up to ");
        Serial.println(hue);
        break;
      case 'd':
        hue = (256 + hue - 16) % 256;
        Serial.print("Hue down to ");
        Serial.println(hue);
        break;
    }
  }
}

void smart_delay(unsigned long t) {
  const unsigned long stop_time = millis() + t;
  do {
    check_ir();
    check_serial();
    delay(1);
  } while (millis() < stop_time);
}

void loop() {
  smart_delay(1);

  while (state == OFF) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    smart_delay(100);
  }

  while (state == ON) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::White;
    FastLED.show();
    smart_delay(100);
  }

  while (state == COLOR) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(hue, sat, val);
    FastLED.show();
    smart_delay(100);
  }

  while (state == RANDOM) {
    static uint8_t hues[NUM_LEDS];
    for (auto &h : hues) h = random8();
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(hues[i], sat, val);
    FastLED.show();
    smart_delay(500);
  }

  while (state == TEMP) {
    int temp_reading = analogRead(TEMP_PIN);
    double tempK = log(10000.0 * ((1024.0 / temp_reading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK); // Kelvin
    float tempC = tempK - 273.15; // Celcius
    float tempF = (tempC * 9.0) / 5.0 + 32.0; // Fahrenheit
    int temp = (int)(tempF + 0.5);
    int tens = (int)(temp / 10);
    int ones = temp - tens * 10;
    for (int i = 0; i < ones; i++)
      leds[i] = CRGB::Blue;
    for (int i = ones; i < ones + tens; i++)
      leds[i] = CRGB::Red;
    for (int i = ones + tens; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    Serial.print("Temperature ");
    Serial.println(temp);
    smart_delay(500);
  }

  while (state == MOVE) {
    // Forward
    for (int i = 1; i <= NUM_LEDS - 2; i++) {
      for (int j = 0; j < NUM_LEDS; j++)
        leds[j] = CRGB::Black;
      leds[i] = CHSV(hue, sat, val);
      leds[i - 1] = CHSV(hue, sat, val / 2);
      leds[i + 1] = CHSV(hue, sat, val / 2);
      FastLED.show();
      smart_delay(100);
      if (state != MOVE) break;
    }

    if (state != MOVE) break;

    // Back
    for (int i = NUM_LEDS - 2; i >= 1; i--) {
      for (int j = 0; j < NUM_LEDS; j++)
        leds[j] = CRGB::Black;
      leds[i] = CHSV(hue, sat, val);
      leds[i - 1] = CHSV(hue, sat, val / 2);
      leds[i + 1] = CHSV(hue, sat, val / 2);
      FastLED.show();
      smart_delay(100);
      if (state != MOVE) break;
    }
  }

  while (state == XMAS) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0)
        leds[i] = CRGB::Red;
      else
        leds[i] = CRGB::Green;
    }
    FastLED.show();
    smart_delay(1000);

    if (state != XMAS) break;

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0)
        leds[i] = CRGB::Green;
      else
        leds[i] = CRGB::Red;
    }
    FastLED.show();
    smart_delay(1000);
  }

}
