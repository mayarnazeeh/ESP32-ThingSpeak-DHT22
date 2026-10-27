/*
 * ESP32 -> ThingSpeak (DHT22)
 * Student: Mayar Othman
 * University ID: 12323342
 * DHT22 DATA pin -> GPIO 15
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ---------- Wi-Fi (Wokwi) ----------
const char* WIFI_SSID     = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const int   WIFI_CHANNEL  = 6;   // Wokwi-GUEST runs on channel 6 (faster connection)

// ---------- ThingSpeak ----------
const char* THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";   // replace with your channel's Write API Key
const char* THINGSPEAK_URL     = "http://api.thingspeak.com/update";

// ---------- Student info ----------
const char* UNIVERSITY_ID = "12323342";

// ---------- DHT22 ----------
#define DHT_PIN  15
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

// Send every 25 seconds (ThingSpeak free limit is 15s minimum)
const unsigned long SEND_INTERVAL = 25000;
unsigned long lastSend = 0;

void connectWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    attempts++;
    Serial.printf("  attempt %d -> status=%d\n", attempts, WiFi.status());

    // Retry from scratch every 15 seconds
    if (attempts % 15 == 0) {
      Serial.println("  Retrying Wi-Fi connection...");
      WiFi.disconnect();
      delay(500);
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
    }
  }

  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
}

void sendToThingSpeak(float temperature, float humidity) {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  HTTPClient http;

  // University ID is sent in the "status" parameter of the request
  String url = String(THINGSPEAK_URL) +
               "?api_key=" + THINGSPEAK_API_KEY +
               "&field1=" + String(temperature, 1) +
               "&field2=" + String(humidity, 1) +
               "&status=UniversityID_" + UNIVERSITY_ID;

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String response = http.getString();
    Serial.printf("[ID %s] HTTP %d | Entry ID: %s\n",
                  UNIVERSITY_ID, httpCode, response.c_str());
  } else {
    Serial.printf("[ID %s] Request failed: %s\n",
                  UNIVERSITY_ID, http.errorToString(httpCode).c_str());
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("=== ESP32 -> ThingSpeak ===");
  Serial.printf("Student: Mayar Othman | University ID: %s\n", UNIVERSITY_ID);

  dht.begin();
  connectWiFi();
}

void loop() {
  if (millis() - lastSend >= SEND_INTERVAL || lastSend == 0) {
    lastSend = millis();

    float temperature = dht.readTemperature();
    float humidity    = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT22 sensor!");
      return;
    }

    Serial.printf("[ID %s] Temperature: %.1f C | Humidity: %.1f %%\n",
                  UNIVERSITY_ID, temperature, humidity);

    sendToThingSpeak(temperature, humidity);
  }
}
