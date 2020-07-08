#include <SR04.h>

#define ECHO_PIN 11
#define TRIG_PIN 12
#define BUZZER_PIN 13
#define ALARM_DISTANCE 60 // cm

struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
} Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
} Length;

int tempo = 400;
long hits = 0;

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

void setTone(int note, int duration) {
  tone(BUZZER_PIN, note);
  delay(duration);
  noTone(BUZZER_PIN);
}

void sing() {
  setTone(Music.B, tempo * Length.one);
  setTone(Music.E, tempo * Length.one_half);
  setTone(Music.G, tempo * Length.half);
  setTone(Music.F, tempo * Length.one);
  setTone(Music.E, tempo * Length.two);
  setTone(Music.B2, tempo * Length.one);
  setTone(Music.A2, tempo * Length.two_half);
  setTone(Music.Fs, tempo * Length.two_half);

  setTone(Music.E, tempo * Length.one_half);
  setTone(Music.G, tempo * Length.half);
  setTone(Music.F, tempo * Length.one);
  setTone(Music.Ds, tempo * Length.two);
  setTone(Music.F, tempo * Length.one);
  setTone(Music.B, tempo * Length.two_half);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  long distance = sr04.Distance(); // Get current distance from sensor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < ALARM_DISTANCE) {
    hits++;
  } else {
    hits = 0;
  }
  Serial.println("Hits: ");
  Serial.println(hits);

  if (hits >= 5) {
    sing();
    hits = 0;
    delay(60000);
  }
  delay(100);
}
