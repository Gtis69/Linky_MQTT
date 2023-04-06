/**
 * Author GTIS69
 *
 */
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "Api.h"

// Replace the next variables with your SSID/Password combination
const char* hostName = "Linky";
const char* ssid = "--- SSID_WIFI ---";
const char* password = "--- PASSWORD ---";

// Add your MQTT Broker IP address:
const char* mqtt_server = "--- IP BROCKER MQTT ---";
const char* mqtt_id = "--- USER NAME ---";
const char* mqtt_password = "--- PASSWORD ---";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

void Api_setup() {
  
  Api_setup_wifi();
  
  client.setServer(mqtt_server, 1883);
}

void Api_setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  IPAddress ip(192, 168, 1, 100); // <-------------- IP STATIC ---------------
  IPAddress subnet(255, 255, 255, 0);
  IPAddress gateway(0, 0, 0, 0);
  IPAddress dns(0, 0, 0, 0);
  WiFi.config(ip, dns, gateway, subnet);

  WiFi.hostname(hostName);
  WiFi.begin(ssid, password);
  //WiFi.printDiag(Serial);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial1.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void Api_reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Linky", mqtt_id, mqtt_password)) {
      Serial.println("connected");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void Api_loop() {
  long now = millis();
  
  if (!client.connected()) {
    Api_reconnect();
  }
  else if (now - lastMsg > 1000) {
      lastMsg = now;      
      client.loop();
  }
}

void Api_Send(String strTopic, String strValue) {
  
  char tempStringTopic[1200];
  char tempStringValue[1200];
  
  strTopic.toCharArray(tempStringTopic, 1200);
  strValue.toCharArray(tempStringValue, 1200);
  
  client.publish(tempStringTopic, tempStringValue);
  
}
