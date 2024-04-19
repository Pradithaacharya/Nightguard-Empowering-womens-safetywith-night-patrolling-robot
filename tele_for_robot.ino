#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Replace with your network credentials
const char* ssid = "Pramitha";
const char* password = "pramitha03";

// Initialize Telegram BOT
#define BOTtoken "6609562237:AAHMbgumAroX4ZY4_9CA17VwhN_y4TsZVk0" // your Bot Token
#define CHAT_ID "1275967165" // your Chat ID


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);

  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Send a "Hello, World!" message to Telegram

}

void loop() {
  // Nothing to do here
  bot.sendMessage(CHAT_ID, "Sound detected", "");
  bot.sendMessage(CHAT_ID, "Check camera feed", "");
  //Serial.println("hello");
}
