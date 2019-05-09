#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 7
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

int alarmTop = 8;
int alarmLandingTop = 11;
int alarmLandingBottom = 13;
int alarmBottom = 9;
int ledPin = 7;
int valueTop;
int valueLandingTop;
int valueLandingBottom;
int valueBottom;
unsigned int timeOut = 60000;
int downUp;
int lastAlarm;

void setup() {
  // put your setup code here, to run once:

  delay(3000);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  //FastLED.setBrightness(50)

  pinMode(alarmTop, INPUT);
  pinMode(alarmLandingTop, INPUT);
  pinMode(alarmLandingBottom, INPUT);
  pinMode(alarmBottom, INPUT);
  pinMode(ledPin, OUTPUT);

  FastLED.clear();
  delay(100000);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  valueTop = digitalRead(alarmTop);
  valueLandingTop = digitalRead(alarmLandingTop);
  valueLandingBottom = digitalRead(alarmLandingBottom);
  valueBottom = digitalRead(alarmBottom);

  if (valueTop == HIGH) {
    /*
    if (lastAlarm = 2) {
      return;
    }
    */
    timeOut = millis();
    downUp = 2;
    lastAlarm = 1;
    topStairsDown();
  }

  if (valueLandingTop == HIGH) {
    /*
    if (lastAlarm = 1) {
      return;
    }
    */
    timeOut = millis();
    downUp = 1;
    lastAlarm = 2;
    topStairsUp();
  }

  if (valueLandingBottom == HIGH) {
    /*
    if (lastAlarm = 4) {
      return;
    }
    */
    timeOut = millis();
    downUp = 2;
    lastAlarm = 3;
    bottomStairsDown();
  }
  if (valueBottom == HIGH) {
    /*
    if (lastAlarm = 3) {
      return;
    }
    */
    timeOut = millis();
    lastAlarm = 4;
    downUp = 1;
    bottomStairsUp();
  }

  if (timeOut + 10000 < millis() && timeOut + 15000 < millis()) {
    if (downUp = 2) {
      for (int i = 0; i <= 149; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(10);
    }
    }
    if (downUp = 1) {
      for (int i = 149; i >= 0; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(10);
    }
    }
    lastAlarm = 0;
    downUp = 0;
  }
}

void topStairsDown() {
  Serial.println("Detected Top");
  for (int i = 0; i <= 100; i++) {
    leds[i] = CRGB::SpringGreen;
    FastLED.show();
    delay(10);
  }
}

void topStairsUp() {
  Serial.println("Detected Landing Top");
  for (int i = 100; i >= 0; i--) {
    leds[i] = CRGB::SpringGreen;
    FastLED.show();
    delay(10);
  }
}

void bottomStairsDown() {
  Serial.println("Detected Landing Bottom");
  for (int i = 100; i < 149; i++) {
    leds[i] = CRGB::SpringGreen;
    FastLED.show();
    delay(10);
  }
}

void bottomStairsUp() {
  Serial.println("Detected Bottom");
  for (int i = NUM_LEDS; i >= 100; i--) {
    leds[i] = CRGB::SpringGreen;
    FastLED.show();
    delay(10);
  }
}
