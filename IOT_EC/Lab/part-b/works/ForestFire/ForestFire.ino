#define BLYNK_TEMPLATE_ID "TMPL3R-rLugGx"
#define BLYNK_TEMPLATE_NAME "forest fire"
#define BLYNK_AUTH_TOKEN "4EXcOEjQGmbq3t6HjHr4kGx3paNtIs4x"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include<string.h>

// Wi-Fi credentials
#define WIFI_SSID "POCO M2"
#define WIFI_PASSWORD "hellomom"

BlynkTimer timer;

// Define the pins for the smoke sensor, flame sensor, and buzzer
#define LED_PIN 2
#define SMOKE_SENSOR_PIN 34  // GPIO pin for Smoke sensor
#define FLAME_SENSOR_PIN 35  // GPIO pin for Flame sensor


  void setup() {
    // Initialize serial communication at a baud rate of 115200
    Serial.begin(115200);
    
    // Configure the LED_PIN as an output
    pinMode(LED_PIN, OUTPUT);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected to Wi-Fi");

    // Connect to Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

    // Start with the LED turned off
    digitalWrite(LED_PIN, LOW);
    timer.setInterval(500, senddata);
    pinMode(SMOKE_SENSOR_PIN, INPUT);
    pinMode(FLAME_SENSOR_PIN, INPUT);
  }


void senddata() {
    String smoke = "Smoke detected";
    String flame = "Flame detected";
    String safe = "Safe!!";
    int smokeDetected = digitalRead(SMOKE_SENSOR_PIN); // 1 if smoke detected, 0 if not
    int flameDetected = digitalRead(FLAME_SENSOR_PIN); // 1 if flame detected, 0 if not
    Serial.println(smokeDetected);
    Serial.println(flameDetected);
    if(smokeDetected && flameDetected)
    {
      Blynk.virtualWrite(V0,smoke);
      Blynk.virtualWrite(V2,1);
      Blynk.virtualWrite(V1,flame);
      Blynk.virtualWrite(V3,1);
    }
    else if(smokeDetected)
    {
      Blynk.virtualWrite(V0,smoke);
      Blynk.virtualWrite(V2,1);
      Blynk.virtualWrite(V1,"No flame");
      Blynk.virtualWrite(V3,0);
    }
    else if(flameDetected)
    {
      Blynk.virtualWrite(V0,"No smoke");
      Blynk.virtualWrite(V2,0);
      Blynk.virtualWrite(V1,flame);
      Blynk.virtualWrite(V3,1);
    }
    else
    {
      Blynk.virtualWrite(V0,safe);
      Blynk.virtualWrite(V2,0);
      Blynk.virtualWrite(V1,safe);
      Blynk.virtualWrite(V3,0);
    }
}


void loop() {
  Blynk.run();
  timer.run();
}
