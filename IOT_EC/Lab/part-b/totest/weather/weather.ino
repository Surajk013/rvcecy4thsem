#define DHTPIN 4          // Pin connected to the DHT sensor (G4 on ESP32)
#define DHTTYPE DHT11     // DHT 11 sensor type
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_NAME "Weather Monitoring"
#define BLYNK_AUTH_TOKEN "z-sbAeM7I5PVVrVQbB4J7QsoAzh4GFub"
#define BLYNK_TEMPLATE_ID "TMPL3a6lUK7QQ"

#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO M2";     // Type your WiFi name
char pass[] = "hellomom";   // Type your WiFi password

DHT dht(DHTPIN, DHTTYPE);

// Define the temperature threshold
#define TEMP_THRESHOLD 35.0  // Temperature in Celsius
#define LED_PIN 2            // Define the LED pin (GPIO 2 on ESP32)

void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting the setup"));
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  pinMode(LED_PIN, OUTPUT); // Initialize the LED pin as an output

  // Wait a few seconds between measurements.
  delay(2000);

  Serial.println(F("DHT test!"));
}

void loop() {
  Blynk.run();
  
  // Reading temperature and humidity data
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from the DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C"));

  // Send data to Blynk
  Blynk.virtualWrite(V1, h);  // Send humidity to virtual pin V1
  Blynk.virtualWrite(V2, t);  // Send temperature to virtual pin V2

  // Check temperature and log event if necessary
  checkTemperature(t);
}

// Function to check temperature and log event
void checkTemperature(float temperature) {
  if (temperature > TEMP_THRESHOLD) {
    // Log the event to Blynk
    Blynk.logEvent("tempalert", "Temperature is high");
  }
}

BLYNK_WRITE(V0) { // Button Widget is writing to pin V0
  int buttonState = param.asInt();
  
  Serial.print(F("Button state: "));
  Serial.println(buttonState);

  if (buttonState == 1) { // If button is pressed
    Serial.println(F("Button pressed"));
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off the LED
    Serial.println(F("Button released"));
  }
}
