#define BLYNK_TEMPLATE_ID "TMPL34bk9gCJ9"
#define BLYNK_TEMPLATE_NAME "smart light"
#define BLYNK_AUTH_TOKEN "vEQPCvQDgbMCoDH5MufuqKr7u0AWMcTm" // Type your Blynk auth Token

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO M2";     // Type your WiFi name
char pass[] = "hellomom";        // Type your WiFi password

const int ldrPin = 34; // ADC1_CH6 on ESP32
int ledPin = 13; // GPIO13 of ESP32

void setup() {
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // Set the LED pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the LDR value
  int ldrValue = analogRead(ldrPin);
  
  // Send the LDR value to the Blynk app on Virtual Pin V2
  Blynk.virtualWrite(V2, ldrValue);
  Serial.println(ldrValue);

  if (ldrValue <= 500) {  // Adjust the threshold value as needed
    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(V0, 0);
    Serial.println("LED Off");
  } else {
    digitalWrite(ledPin, HIGH);
    Blynk.virtualWrite(V0, 1);
    Serial.println("LED On");
  }

  Blynk.run();
}
