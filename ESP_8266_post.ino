#include <ESP8266WiFi.h>
const char* ssid     = "ssid";
const char* password = "password";

const char* host = "server_name";

const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  delay(100);
  //Wifiの機能を起動する
  WiFi.begin(ssid, password);

  //WiFiが起動したか確認する
  //WiFiが起動するまで待つ
  while (Is_wifi_started()) {
    delay(500);
    Serial.print(".");
  }

  //postする
  post(host, httpPort, 20, 50);

}

void post(const char* url, int port, int Temperature, int Humidity) {

  String data = "temperature=" + String(Temperature) + "&" + "humidity=" + String(Humidity);

  WiFiClient client;
  if (!client.connect(*url, port)) {
    Serial.println("connection failed");
    return;
  }

  client.println("POST / HTTP/1.1\nHost: server_name\nAccept: */*\nContent-Type: application/x-www-form-urlencoded\nContent-Length: ");
  client.println(data.length());
  client.println();
  client.print(data);

  if (client.connected()) {
    client.stop();
  }
}

boolean Is_wifi_started() {
  return (WiFi.status() != WL_CONNECTED);
}





void loop() {

  delay(5000);
}

