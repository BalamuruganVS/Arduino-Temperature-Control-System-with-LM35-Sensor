#include <elapsedMillis.h>

// Define constants
const int LM35_PIN = A0;            // LM35 temperature sensor pin
const int LED_PIN = 13;             // Onboard LED pin
const int TEMPERATURE_THRESHOLD = 30;
const int BLINK_INTERVAL_LOW_TEMP = 250;
const int BLINK_INTERVAL_HIGH_TEMP = 500;

// Time variables
elapsedMillis blinkTimer;  // Timer for LED blinking

// Function prototypes
float readTemperature();
void blinkLED(long interval);

void setup() {
  pinMode(LM35_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read temperature from LM35 sensor
  float temperature = readTemperature();

  // Check temperature conditions and control LED accordingly
  if (temperature < TEMPERATURE_THRESHOLD) {
    blinkLED(BLINK_INTERVAL_LOW_TEMP);
  } else {
    blinkLED(BLINK_INTERVAL_HIGH_TEMP);
  }
}

// Function to read temperature from LM35 sensor
float readTemperature() {
  int sensorValue = analogRead(LM35_PIN);
  float voltage = (sensorValue / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100.0;
  return temperature;
}

// Function to control LED blinking based on temperature
void blinkLED(long interval) {
  // Check if the LED needs to be blinked
  if (blinkTimer >= interval) {
    // Reset the timer
    blinkTimer = 0;

    // Toggle the LED state
    if (digitalRead(LED_PIN) == LOW) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
