#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "VaxSafe"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHTesp.h"

// Network Config
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Real hardware ke liye apna WiFi Name
char pass[] = "";            // Real hardware ke liye apna Password
const char* serverUrl = "http://YOUR_LAPTOP_IP:5000/vaxsafe/telemetry";

// Hardware Pins
const int DHT_PIN = 15;
const int RED_LED = 12;
const int GREEN_LED = 14;
const int BUZZER_PIN = 13;

DHTesp dht;
BlynkTimer timer;

void sendDataToAll() {
  float temp = dht.getTemperature();
  if (isnan(temp)) return;

  // 1. Local Edge Alerts
  if (temp > 8.0 || temp < -2.0) {
    digitalWrite(RED_LED, HIGH); digitalWrite(GREEN_LED, LOW);
    tone(BUZZER_PIN, 1000, 100);
  } else {
    digitalWrite(RED_LED, LOW); digitalWrite(GREEN_LED, HIGH);
    noTone(BUZZER_PIN);
  }

  // 2. Send to Blynk Dashboard
  Blynk.virtualWrite(V0, temp);

  // 3. Send to Python AI & Blockchain Server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["temperature"] = temp;
    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);
    if (httpCode > 0) {
      String response = http.getString();
      StaticJsonDocument<500> resDoc;
      deserializeJson(resDoc, response);

      // Backend se aane wali AI analysis Blynk par dikhana
      Blynk.virtualWrite(V1, resDoc["ai_health"]);
      Blynk.virtualWrite(V2, resDoc["blockchain_proof"]);
    }
    http.end();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.setup(DHT_PIN, DHTesp::DHT22);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, sendDataToAll); // Har 3 second mein update
}

void loop() {
  Blynk.run();
  timer.run();
}
