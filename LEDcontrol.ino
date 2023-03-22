
#include <Arduino.h>
#include <ESP8266WiFi.h> // For ESP8266
#include <PubSubClient.h>
#include <ArduinoJson.h> 

// Replace with your Wi-Fi credentials and ThingsBoard token
const char* ssid = "";
const char* password = "";
const char* token = "";

// Light Pin
const int lightPin = 5; // Change this to your LED pin number

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String payloadStr;
  for (unsigned int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }

  // bool state = payloadStr == "{\"method\":\"setValue\",\"params\":true}";
  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, payloadStr);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract the "params" value
  bool state = doc["params"];

  Serial.println(payloadStr);
  digitalWrite(lightPin, state ? HIGH : LOW);
  Serial.println(state ? "Light ON" : "Light OFF");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", token, NULL)) {
      Serial.println("connected");
      client.subscribe("v1/devices/me/rpc/request/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer("demo.thingsboard.io", 1883);
  client.setCallback(callback);

  pinMode(lightPin, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}