#define BLYNK_TEMPLATE_ID "TMPL3Qaz55FmO"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define TRIGGER 2  // GPIO 2 for Trigger
#define ECHO 4     // GPIO 4 for Echo

#define BLYNK_PRINT Serial

char auth[] = "YCNTkhmW6f5wck7DSPl2nzELVaqk2JVK";
char ssid[] = "POCO M2";
char pass[] = "hellomom";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  // Display distance on V0
  Blynk.virtualWrite(V0, distance);
  
  if (distance <= 40) {
    Blynk.virtualWrite(V1, 1);  // Occupied
    Blynk.virtualWrite(V2, 1);  // LED On
  } else {
    Blynk.virtualWrite(V1, 0);  // Not Occupied
    Blynk.virtualWrite(V2, 0);  // LED Off
  }
  
  Serial.print(distance);
  Serial.println(" Centimeter");
  
  Blynk.run();  // Process Blynk
  delay(200);   // Control loop speed
}
