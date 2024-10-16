#define BLYNK_TEMPLATE_NAME "Forest Fire"
#define BLYNK_TEMPLATE_ID "TMPL3ZFLhV56F"
#define BLYNK_AUTH_TOKEN "yx8_HO-4SGZFl0gHLqehz_HLSAkeyEPo"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

#define WIFI_SSID "Garuda 2.4Ghz"
#define WIFI_PASSWORD "iamspeeeeeed"

#define SMOKE_SENSOR_PIN 34       // Analog pin for smoke sensor
#define DHTPIN 4                  // Digital pin for DHT sensor
#define DHTTYPE DHT11             // DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
  Serial.println("Connected to Wi-Fi");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

  dht.begin();
  pinMode(SMOKE_SENSOR_PIN, INPUT);
}

void loop() {
  Blynk.run();
  sendSensorDataToBlynk();  // Call the function to send sensor data
}

void sendSensorDataToBlynk() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  int smokeLevel = analogRead(SMOKE_SENSOR_PIN);

  // Scale the raw analog value to a percentage (0% to 100%)
  int smokePercent = map(smokeLevel, 0, 1023, 0, 100); // Adjust the max value based on your ADC resolution
  
  // Ensure the percentage is within the valid range
  smokePercent = constrain(smokePercent, 0, 100);
  
  Blynk.virtualWrite(V0, humidity);    // Send humidity to Blynk
  Blynk.virtualWrite(V1, temperature); // Send temperature to Blynk
  Blynk.virtualWrite(V2, smokePercent);  // Send smoke level percentage to Blynk

  // Fire detection logic
  if (smokePercent > 70 || temperature > 50) { // Adjust threshold as needed
    // Trigger alarm or take action
    Serial.println("Fire detected!");
    //Blynk.notify("Fire detected! Please check immediately.");
  }
}
