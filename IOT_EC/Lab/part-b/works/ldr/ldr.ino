#define LED_PIN 4         // GPIO pin where the LED is connected
#define LDR_PIN 34        // GPIO pin where the LDR is connected (use an ADC1 pin)

#define BLYNK_TEMPLATE_ID "TMPL3DrVUmhYp"
#define BLYNK_TEMPLATE_NAME "ldr"
#define BLYNK_AUTH_TOKEN "_NKaO-IGilhNCvzazpUJfekrmS7CRAGG"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi credentials
#define WIFI_SSID "POCO M2"
#define WIFI_PASSWORD "hellomom"

BlynkTimer timer;

// Variables for mode control
bool manualMode = false;
int ledState = 0;  // Keep track of manual LED state

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

  // Set a timer to send LDR values every 2 seconds
  timer.setInterval(2000, sendLDR);
}

void sendLDR() {
  if (!manualMode) {  // Only control the LED automatically if manual mode is off
    // Read the analog value from the LDR
    int ldrValue = analogRead(LDR_PIN);

    // Print the LDR value to the Serial Monitor
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Send LDR value to Blynk app
    Blynk.virtualWrite(V1, ldrValue);  // V1 is a virtual pin for LDR value

    // Control the LED based on the LDR value
    if (ldrValue > 3900) {  // Adjust this threshold value as per your requirement
      digitalWrite(LED_PIN, HIGH);  // Turn on the LED
      Serial.println("LED ON");
    } else {
      digitalWrite(LED_PIN, LOW);  // Turn off the LED
      Serial.println("LED OFF");
    }
  }
}

void loop() {
  Blynk.run();
  timer.run(); // Run the timer to send the LDR value at intervals
}

// Blynk function to control LED state in manual mode (V0 switch)
BLYNK_WRITE(V0) {
  if (manualMode) {  // Only control the LED if manual mode is active
    ledState = param.asInt();  // Get the state of the switch (1 for ON, 0 for OFF)
    if (ledState == 1) {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED
      Serial.println("LED ON (Manual Mode)");
    } else {
      digitalWrite(LED_PIN, LOW);  // Turn off the LED
      Serial.println("LED OFF (Manual Mode)");
    }
  }
}

// Blynk function to toggle between automatic and manual mode (V2 switch)
BLYNK_WRITE(V2) {
  int mode = param.asInt();  // Get the state of the switch (1 for Manual, 0 for Auto)
  if (mode == 1) {
    manualMode = true;
    Serial.println("Manual Mode ON");
  } else {
    manualMode = false;
    Serial.println("Automatic Mode ON");
  }
}
