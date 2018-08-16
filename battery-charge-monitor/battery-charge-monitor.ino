#include <ESP8266WiFi.h>

const char* ssid        = "YourSSID";
const char* password    = "YourPW";
const char* host        = "192.168.xxx.yyy";
const int   httpPort    = 80;
const char* apiurl      = "/your/api/to/save/values/of/solarcharger/"; // <- voltage will be added here (see line 60)

void deep_sleep_minutes(int minutes) {
  if (minutes > 70)
    minutes = 70;
  unsigned int microseconds = minutes * 60000000;
  Serial.print("Going into deep sleep for ");
  Serial.print(minutes);
  Serial.println(" minutes");
  ESP.deepSleep(microseconds);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  pinMode(A0, INPUT);

  Serial.println();
  Serial.println();
  Serial.println("Setup ready");
}

void loop() {
  unsigned int raw = 0;
  float volt = 0.0;
  float volt2 = 0.0;
  
  raw = analogRead(A0);
  volt = (raw / 1023.0) * 4.2;

  Serial.print("RAW: ");
  Serial.print(raw);
  Serial.print(" -> ");
  Serial.print(volt);
  Serial.println(" V");

  Serial.println("Connect to WiFi network");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Sending value");
  String v=String(volt);// change float into string
  // make TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  String url = String(apiurl) + String(volt);
 
// Send request to the server
  client.print(String("GET " + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n"));
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  
  deep_sleep_minutes(15);
}

