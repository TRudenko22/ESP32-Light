#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define LED_BUILTIN 2
#define TRIGGER 23

const char* SSID = "SSID";
const char* PASSWORD = "PASSWORD";

WebServer server(80);

void on_Connect() {
  server.send(200, "text/html", "Take me to your leader\n"); 
}

void set_On() {
  server.send(200, "text/html", "Setting PIN 23 ON\n");
  digitalWrite(TRIGGER, HIGH);
}

void set_Off() {
  server.send(200, "text/html", "Setting PIN 23 OFF\n");
  digitalWrite(TRIGGER, LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGER, OUTPUT);

  Serial.begin(115200); 
  Serial.print("Connecting to "); Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("...................");
  }

  for (int i=0; i<5; i++) {
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
  }

  Serial.print("Connection: "); Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, HIGH);

  // GET
  server.on("/", on_Connect);
  server.on("/on", set_On);
  server.on("/off", set_Off);

  server.begin();
}

void loop() {
  server.handleClient();
}
