#define BLYNK_TEMPLATE_ID "TMPL3DntmoYyh"
#define BLYNK_TEMPLATE_NAME "intrusion detection"
#define BLYNK_AUTH_TOKEN "tEPkwQpQml5wnzTtl-_XpgdaKDbQ5DbI"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "POCO M2";  // Replace with your Wi-Fi SSID
char pass[] = "hellomom";  // Replace with your Wi-Fi Password

#define TRIG_PIN 2 // Pin for Ultrasonic sensor TRIG
#define ECHO_PIN 4  // Pin for Ultrasonic sensor ECHO
#define LED_PIN 2    // Pin for LED

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Blynk.run();
  detectIntrusion();
}

void detectIntrusion() {
  long duration;
  int distance;

  // Trigger the ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance to Blynk
  Blynk.virtualWrite(V0, distance);

  // If the distance is below the threshold (e.g., 50 cm), turn on the LED
  if (distance < 50) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    Serial.println("Intrusion detected!");
    Blynk.logEvent("intrusion_alert", "Intrusion detected! Please check immediately.");
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off LED
  }

  delay(1000); // Wait for 1 second before the next measurement
}
