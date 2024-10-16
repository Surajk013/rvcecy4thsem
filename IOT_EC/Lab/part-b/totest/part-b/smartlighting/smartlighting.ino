#define BLYNK_TEMPLATE_NAME "Forest Fire"
#define BLYNK_TEMPLATE_ID "TMPL3ZFLhV56F"
#define BLYNK_AUTH_TOKEN "yx8_HO-4SGZFl0gHLqehz_HLSAkeyEPo"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "yx8_HO-4SGZFl0gHLqehz_HLSAkeyEPo";  // Replace with your Blynk Auth Token
char ssid[] = "Garuda 2.4Ghz";         // Your WiFi name
char pass[] = "iamspeeeeeed";      // Your WiFi password

const int ldrPin = A0; // LDR module connected to A0
int ledPin = 4;       // LED connected to D1

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read LDR value
  int ldrValue = analogRead(ldrPin);
  
  // Print LDR value to Serial Monitor
  Serial.println(ldrValue);

  // Control LED based on LDR value
  if (ldrValue < 500) { // Adjust the threshold as needed
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  Blynk.run();
  delay(1000); // Adjust delay as needed
}
