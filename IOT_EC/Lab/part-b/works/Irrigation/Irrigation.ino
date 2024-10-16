#define BLYNK_TEMPLATE_ID "TMPL3Nb4vd5RN"
#define BLYNK_TEMPLATE_NAME "smart irrigation"
#define BLYNK_AUTH_TOKEN "OXUaEqWNAQGl6l18apch5sCr_aN8ElvV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include<string.h>

// Wi-Fi credentials
#define WIFI_SSID "POCO M2"
#define WIFI_PASSWORD "hellomom"

BlynkTimer timer;
// Define the pin for the moisture sensor and water pump relay
#define MOISTURE_SENSOR_PIN 34  // GPIO pin for Moisture sensor
#define LED_PIN 2

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
  // Set up Moisture sensor pin
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
}
void senddata() {
    String low = "Water Low!!";
    String normal = "Normal!!";
    int moistureValue = analogRead(MOISTURE_SENSOR_PIN);
    Serial.println(moistureValue);
    Blynk.virtualWrite(V1,moistureValue);
    if(moistureValue > 2000 )
    {
      Serial.println("LOW!");
      Blynk.virtualWrite(V0,low);
      Blynk.virtualWrite(V2,1);
    }
    else
    {
      Serial.println("Normal!!");
      Blynk.virtualWrite(V0,normal);
      Blynk.virtualWrite(V2,0);
    }
}
void loop() {
  Blynk.run();
  timer.run();
}
