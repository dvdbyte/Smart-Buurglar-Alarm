#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>



const char* ssid = "Wifi-Name";         //Replace with your wifi Name
const char* password = "Wifi-Password"; //Replace with your wifi password


#define BOTtoken "5939333488:AAEf0A2acAVJFZbQ60z7Gt0TUPCRzOWFh6c"
#define CHAT_ID "5066642540"

#define Sensor D0
#define LEDR D3
#define LEDG D4
#define Buzzer D5

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  pinMode(Sensor, INPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);

  bot.sendMessage(CHAT_ID, "System started", "");
  delay(100);

}
void loop() {
  bool value = digitalRead(Sensor);
  Serial.println(value);
  if (value == 1) {
    digitalWrite(LEDR, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LEDG, LOW);
    bot.sendMessage(CHAT_ID, "Motion detected!!", "");
  } else if (value == 0) {
    digitalWrite(LEDR, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(LEDG, HIGH);
  }
}