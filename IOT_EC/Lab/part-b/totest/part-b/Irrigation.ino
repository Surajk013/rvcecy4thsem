#define BLYNK_TEMPLATE_ID "TMPL3DpBnXeTB"
#define BLYNK_TEMPLATE_NAME "Monitor ESP32 with sensors"
#define BLYNK_AUTH_TOKEN "WdyHk7hO7GDJTW2JWtxJmn0APpySO8xX"
#define DHTPIN 4          // Pin connected to the DHT sensor (G4 on ESP32)
#define DHTTYPE DHT11     // DHT 11 sensor type

#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>   // Include the Blynk library

#define WIFI_SSID "Shree"
#define WIFI_PASSWORD "12344321"

DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial
#define SOIL_MOISTURE_PIN 34

// Define the range for the soil moisture sensor
int dryValue = 4095;  // Sensor value when the soil is completely dry
int wetValue = 0;     // Sensor value when the soil is completely wet
int humidity = 0;
int temp = 0;
int soilMoisturePercent = 0;
int dryThresholdPercentage = 10;
BlynkTimer timer;

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  dht.begin();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD, "blynk.cloud", 80);  
  
  // Setup Blynk Timer to read sensor values periodically
  timer.setInterval(2000L, sendSensorDataToBlynk);
}

void sendSensorDataToBlynk() {
  readHumidity();
  readTemp();
  readSoilMoisture();
  
  Serial.println("Humidity: " + String(humidity) + "%, Temperature: " + String(temp) + "°C, Soil Moisture: " + String(soilMoisturePercent) + "%");
  // Check if moisture level is below the threshold
  if (soilMoisturePercent < dryThresholdPercentage) { // Threshold in percentage
    Serial.println("\nSoil is dry! Consider watering the plants.");
  } else {
    Serial.println("\nSoil moisture is sufficient.");
  }
  
  Blynk.virtualWrite(V0, humidity);           // Send humidity to Blynk
  Blynk.virtualWrite(V1, temp);               // Send temperature to Blynk
  Blynk.virtualWrite(V2, soilMoisturePercent); // Send soil moisture to Blynk
}

void readHumidity() {
  humidity = dht.readHumidity();
}

void readTemp() {
  temp = dht.readTemperature();
}

void readSoilMoisture() {
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  soilMoisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);
}

void loop() {
  Blynk.run();
  timer.run();
}
