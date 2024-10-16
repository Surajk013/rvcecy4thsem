#define BLYNK_TEMPLATE_ID "TMPL3GquHlvXG"
#define BLYNK_TEMPLATE_NAME "weather monitoring"
#define BLYNK_AUTH_TOKEN "06eZTfDyn3sgLBYX2DK9uSE8z1tpWtVI"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// Wi-Fi credentials
#define WIFI_SSID "POCO X3"
#define WIFI_PASSWORD "12345678"

BlynkTimer timer;

// Define the pin and type for the DHT sensor
#define DHT_PIN 33      // GPIO pin for DHT sensor
#define DHT_TYPE DHT22   // DHT11 or DHT22
#define LED_PIN 2

DHT dht(DHT_PIN, DHT_TYPE);



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
  timer.setInterval(2000, senddata);

  // Initialize the DHT sensor
  dht.begin();
}

void senddata() {
    float temperature = dht.readTemperature(); // Get temperature in Celsius
    float humidity = dht.readHumidity();       // Get humidity percentage
    Serial.println(humidity);
    Serial.println(temperature);
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V0, humidity);
}

void loop() {
  Blynk.run();
  timer.run(); 
}
