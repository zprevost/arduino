#include <avr/pgmspace.h>
#include <FastLED.h>

#define DISP_HEIGHT 5 // Height of the physical display in pixels
#define DISP_WIDTH 10 // Width of the physical display in pixels
#define CHAR_WIDTH 5 // Width of each character in pixels
#define MARQ_WIDTH 200 // Width of the display reg in pixels

// FOR LED lights
#define LED_PIN 12
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
byte hue = 125;
byte sat = 255;
byte val = 255;

const byte led_grid[DISP_HEIGHT][DISP_WIDTH] = {
  { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9},
  {19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
  {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
  {39, 38, 37, 36, 35, 34, 33, 32, 31, 30},
  {40, 41, 42, 43, 44, 45, 46, 47, 48, 49}
};

String char_mat_contents = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

const byte char_mat[][DISP_HEIGHT][CHAR_WIDTH] PROGMEM = {
  { // A
    {0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
  },
  { // B
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0},
  },
  { // C
    {0, 0, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1},
  },
  { // D
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0},
  },
  { // E
    {0, 1, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 1},
  },
  { // F
    {0, 1, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
  },
  { // G
    {0, 0, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 1},
  },
  { // H
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
  },
  { // I
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
  },
  { // J
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0},
  },
  { // K
    {0, 1, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 0, 1},
  },
  { // L
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
  },
  { // M
    {1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
  },
  { // N
    {0, 1, 0, 0, 1},
    {0, 1, 1, 0, 1},
    {0, 1, 0, 1, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
  },
  { // O
    {0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0},
  },
  { // P
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
  },
  { // Q
    {0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 1, 1},
    {0, 0, 1, 1, 1},
  },
  { // R
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 0, 1},
  },
  { // S
    {0, 0, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 1, 1, 0},
  },
  { // T
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
  },
  { // U
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0},
  },
  { // V
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
  },
  { // W
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0},
  },
  { // X
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
  },
  { // Y
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
  },
  { // Z
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1},
  },
  { // 0
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // 1
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
  },
  { // 2
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
  },
  { // 3
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // 4
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
  { // 5
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // 6
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // 7
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
  { // 8
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // 9
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
  { // SPACE
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
  },
};

byte marquee[DISP_HEIGHT][MARQ_WIDTH]; // Full marquee of characters to display
int marq_width = 0;

void fill_marquee(String disp_str) {
  int row, col; // Loop variables

  // Convert display string to uppercase
  disp_str.toUpperCase();

  // Initialize marquee
  for (row = 0; row < DISP_HEIGHT; row++)
    for (col = 0; col < MARQ_WIDTH; col++)
      marquee[row][col] = 0;

  // Fill marquee with characters
  marq_width = 0;

  // For each character in the display string
  for (int i = 0; i < disp_str.length(); i++) {
    char letter = disp_str[i];
    int index = char_mat_contents.indexOf(letter);
    Serial.print("Loading ");
    Serial.print(letter);
    Serial.print(" with index ");
    Serial.println(index);

    for (col = 0; col < CHAR_WIDTH; col++) {
      for (row = 0; row < DISP_HEIGHT; row++) {
        // Copy one pixel from character matrix to marquee
        int marq_row = row;
        marquee[marq_row][marq_width] = pgm_read_byte_near(&char_mat[index][row][col]);
      }
      marq_width++;
      if (marq_width == MARQ_WIDTH)
        return;
    }
  }

  return;
}

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to connect
  Serial.println("Ready");

  // Fill the marquee
  fill_marquee("Houston Texas");
  Serial.print("Ended at marq_width: ");
  Serial.print(marq_width - 1);
  Serial.print(" of ");
  Serial.println(MARQ_WIDTH - 1);

  // Print the marquee to the serial port
  for (int row = 0; row < DISP_HEIGHT; row++) {
    for (int col = 0; col < MARQ_WIDTH; col++) {
      if (marquee[row][col])
        Serial.print("#");
      else
        Serial.print(" ");
    }
    Serial.println();
  }
}

void loop() {
  for (int marq_col = 0; marq_col < MARQ_WIDTH - DISP_WIDTH; marq_col++) {
    for (int row = 0; row < DISP_HEIGHT; row++) {
      for (int col = 0; col < DISP_WIDTH; col++) {
        if (marquee[row][marq_col + col])
          leds[led_grid[row][col]] = CRGB::Green;
        else
          leds[led_grid[row][col]] = CRGB::Black;
      }
    }
    FastLED.show();
    delay(200);
    if (marq_col == marq_width)
      break;
  }
}
