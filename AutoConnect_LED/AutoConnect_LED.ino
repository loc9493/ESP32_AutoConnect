#include <WiFi.h>          // Replace with WiFi.h for ESP32
#include <WebServer.h>     // Replace with WebServer.h for ESP32
#include <AutoConnect.h>
#define LED_PIN 2
WebServer Server;          // Replace with WebServer for ESP32
AutoConnect      Portal(Server);
bool LedStatus = LOW;
void rootPage() {
  char content[] = "Hello,  world";
  Server.send(200, "text/plain", content);
}

void successString(String text) {
  Server.send(200, "text/plain", text);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  
  Server.on("/", rootPage);
  Server.on("/led/off", turnOffLED);
  Server.on("/led/on", turnOnLED);
  Server.on("/led/toggle", toggleLED);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void toggleLED() {
  LedStatus = !LedStatus;
  digitalWrite(LED_PIN, LedStatus);
  successString("Toggled");
}

void turnOffLED() {
  LedStatus = LOW;
  digitalWrite(LED_PIN, LedStatus);
  successString("Led Off");
}

void turnOnLED() {
  LedStatus = HIGH;
  digitalWrite(LED_PIN, LedStatus);
  successString("Led On");
}


void loop() {
    Portal.handleClient();
}
