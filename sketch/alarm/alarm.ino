#include <SR04.h>

#define ECHO_PIN 11
#define TRIG_PIN 12
#define BUZZER_PIN 13
#define ALARM_DISTANCE 30 // cm

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

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
    Serial.println("Too close");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    Serial.println("Good distance");
  }

  delay(250);
}
