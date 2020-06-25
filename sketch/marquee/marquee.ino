#include <FastLED.h>

#define DISP_HEIGHT 5 // Height of the physical display in pixels
#define DISP_WIDTH 10 // Width of the physical display in pixels
#define CHAR_WIDTH 5 // Width of each character in pixels
#define REG_WIDTH 100 // Width of the display reg in pixels

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

String char_mat_contents = "MISP";

const byte char_mat[4][DISP_HEIGHT][CHAR_WIDTH] = {
  { // M
    {1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
  },
  { // I
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
  },
  { // S
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  { // P
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
  },
};

byte reg[DISP_HEIGHT][REG_WIDTH]; // Full register of characters to display

int fill_reg(String disp_str) {
  int row, col; // Loop variables

  // Convert display string to uppercase
  disp_str.toUpperCase();

  // Initialize reg
  for (row = 0; row < DISP_HEIGHT; row++)
    for (col = 0; col < REG_WIDTH; col++)
      reg[row][col] = 0;

  // Fill reg with characters
  int reg_col = 0;

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
        // Copy one pixel from character matrix to full display matrix
        int reg_row = row;
        reg[reg_row][reg_col] = char_mat[index][row][col];
      }
      reg_col++;
      if (reg_col == REG_WIDTH)
        return reg_col;
    }
  }

  return reg_col;
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to connect
  Serial.println("Ready");

  // Fill the reg
  int reg_col = fill_reg("mississippi");
  Serial.print("Ended at reg_col: ");
  Serial.print(reg_col - 1);
  Serial.print(" of ");
  Serial.println(REG_WIDTH - 1);

  // Print the reg
  for (int row = 0; row < DISP_HEIGHT; row++) {
    for (int col = 0; col < REG_WIDTH; col++) {
      if (reg[row][col])
        Serial.print("#");
      else
        Serial.print(" ");
    }
    Serial.println();
  }
}

void loop() {
  delay(10);
}
