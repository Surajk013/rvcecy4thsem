
#define BLYNK_TEMPLATE_ID "TMPL3r1ws11_m"
#define BLYNK_TEMPLATE_NAME "smart parking"
#define BLYNK_AUTH_TOKEN "3CcMgugLeWl7pXMFIhVKNLR3F5AZahiw"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include<string.h>

// Wi-Fi credentials
#define WIFI_SSID "POCO M2"
#define WIFI_PASSWORD "hellomom"

BlynkTimer timer;

#define IR_SENSOR_PIN 34  // GPIO pin for PIR Sensor
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
  // Set up PIR sensor and buzzer pins
  pinMode(IR_SENSOR_PIN, INPUT);
}

void senddata() {
  String full = "Full";
  String empty = "Empty";
  int irState = digitalRead(IR_SENSOR_PIN);
    Serial.println(irState);
    if(irState==0)
    {
        Blynk.virtualWrite(V0, full);
        Blynk.virtualWrite(V1,1);
    }
    else
    {
      Blynk.virtualWrite(V0, empty);
      Blynk.virtualWrite(V1, 0);
    }
}

void loop() {
  Blynk.run();
  timer.run();
}
