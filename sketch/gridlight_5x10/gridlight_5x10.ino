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
#define IR_PIN 11
IRrecv ir_receiver(IR_PIN);
decode_results ir_results;

// FOR LED lights
#define LED_PIN 12
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
byte hue = 125;
byte sat = 255;
byte val = 255;

enum STATE {
  OFF,
  WHITE,
  COLOR,
  TEMP,
  RANDOM,
  FLASH,
  SNAKE,
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
  Serial.println("Ready");
}

void check_ir() {
  while (!ir_receiver.isIdle()); // Wait until not busy
  if (ir_receiver.decode(&ir_results)) {
    switch (ir_results.value) {
      case IR_KEY_0:
        state = OFF;
        Serial.println("OFF");
        break;
      case IR_KEY_1:
        state = WHITE;
        Serial.println("WHITE");
        break;
      case IR_KEY_2:
        state = COLOR;
        Serial.println("COLOR");
        break;
      case IR_KEY_3:
        state = TEMP;
        Serial.println("TEMP");
        break;
      case IR_KEY_4:
        state = RANDOM;
        Serial.println("RANDOM");
        break;
      case IR_KEY_5:
        state = FLASH;
        Serial.println("FLASH");
        break;
      case IR_KEY_6:
        state = SNAKE;
        Serial.println("SNAKE");
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
        state = WHITE;
        Serial.println("WHITE");
        break;
      case '2':
        state = COLOR;
        Serial.println("COLOR");
        break;
      case '3':
        state = TEMP;
        Serial.println("TEMP");
        break;
      case '4':
        state = RANDOM;
        Serial.println("RANDOM");
        break;
      case '5':
        state = FLASH;
        Serial.println("FLASH");
        break;
      case '6':
        state = SNAKE;
        Serial.println("SNAKE");
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
  STATE start_state = state;
  while (millis() < stop_time && state == start_state) {
    check_ir();
    check_serial();
    delay(1);
  }
}

void show_digits(int tens_digit, int ones_digit) {
  const byte digit_char[10][5][3] = {
    { // Zero
      {1, 1, 1},
      {1, 0, 1},
      {1, 0, 1},
      {1, 0, 1},
      {1, 1, 1},
    },
    { // One
      {0, 1, 0},
      {0, 1, 0},
      {0, 1, 0},
      {0, 1, 0},
      {0, 1, 0},
    },
    { // Two
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1},
    },
    { // Three
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
    },
    { // Four
      {1, 0, 1},
      {1, 0, 1},
      {1, 1, 1},
      {0, 0, 1},
      {0, 0, 1},
    },
    { // Five
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
    },
    { // Six
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
    },
    { // Seven
      {1, 1, 1},
      {0, 0, 1},
      {0, 0, 1},
      {0, 0, 1},
      {0, 0, 1},
    },
    { // Eight
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
    },
    { // Nine
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
      {0, 0, 1},
      {0, 0, 1},
    },
  };

  // Clear all the lights
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;

  int row_offset = 0;
  int col_offset = 1;
  for (int row = 0; row < 5; row++)
    for (int col = 0; col < 3; col++)
      if (digit_char[tens_digit][row][col] == 1)
        leds[led_grid[row + row_offset][col + col_offset]] = CHSV(hue, sat, val);

  col_offset = 6;
  for (int row = 0; row < 5; row++)
    for (int col = 0; col < 3; col++)
      if (digit_char[ones_digit][row][col] == 1)
        leds[led_grid[row + row_offset][col + col_offset]] = CHSV(hue, sat, val);

  FastLED.show();
}

void loop() {
  smart_delay(1);

  while (state == OFF) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    smart_delay(100);
  }

  while (state == WHITE) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(0, 0, val);
    FastLED.show();
    smart_delay(100);
  }

  while (state == COLOR) {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(hue, sat, val);
    FastLED.show();
    smart_delay(100);
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
    show_digits(tens, ones);
    smart_delay(1000);
  }

  while (state == RANDOM) {
    for (int i = 0; i < NUM_LEDS; i ++) {
      hue = random(0, 256);
      leds[i] = CHSV(hue, sat, val);
    }
    FastLED.show();
    smart_delay(5000);
  }

  while (state == FLASH) {
    for (int i = 0; i < NUM_LEDS; i ++) {
      if (i % 2 == 0) {
        leds[i] = CHSV(hue, sat, val);
      } else {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }
    smart_delay(50);

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        leds[i] = CRGB::Black;
      } else {
        leds[i] = CHSV(hue, sat, val);
      }
      FastLED.show();
    }
    smart_delay(50);
  }

  while (state == SNAKE) {
    // Start the snake
    const int snake_length = 5;
    for (int i = 0; i < snake_length; i++)
      leds[i] = CHSV(hue, sat, val);
    for (int i = snake_length; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    smart_delay(100);

    // Move the snake forwards
    int head_pos = snake_length;
    while (head_pos < NUM_LEDS && state == SNAKE) {
      leds[head_pos] = CHSV(hue, sat, val);
      leds[head_pos - snake_length] = CRGB::Black;
      FastLED.show();
      smart_delay(100);
      head_pos++;
    }

    head_pos = head_pos - snake_length - 1;
    while (head_pos > 0 && state == SNAKE) {
      leds[head_pos] = CHSV(hue, sat, val);
      leds[head_pos + snake_length] = CRGB::Black;
      FastLED.show();
      smart_delay(100);
      head_pos--;
    }
  }

}
