#define BLYNK_TEMPLATE_ID "TMPL3gVAR6TnG"
#define BLYNK_TEMPLATE_NAME "intrusion detection"
#define BLYNK_AUTH_TOKEN "aDVre75Gl3_iICSaEUZa4Q3LlkFMosO1"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include<string.h>

// Wi-Fi credentials
#define WIFI_SSID "POCO M2"
#define WIFI_PASSWORD "hellomom"

BlynkTimer timer;

// Define the pin for the PIR sensor and buzzer
#define IR_SENSOR_PIN 34  // GPIO pin for PIR Sensor
#define BUZZER_PIN 25      // GPIO pin for Buzzer
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
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);  // Ensure the buzzer is off initially
}

void senddata() {
  String safe = "safe!!";
  String intrusion = "Intruder!!";
  int irState = digitalRead(IR_SENSOR_PIN);
    Serial.println(irState);
    if(irState==0)
    {
        digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
        delay(1000);                    // Wait for 2 seconds
        digitalWrite(BUZZER_PIN, LOW);  // Turn off the buzzer
        Blynk.virtualWrite(V0, intrusion);
        Blynk.virtualWrite(V1,1);
    }
    else
    {
      Blynk.virtualWrite(V0, safe);
      Blynk.virtualWrite(V1, 0);
    }
}

void loop()
{
  Blynk.run();
  timer.run();
}
