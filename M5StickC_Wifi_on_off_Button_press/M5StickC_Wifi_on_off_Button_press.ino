#include <WiFi.h>
#include <M5StickC.h>

const char* ssid = "tkwtic24";
const char* password = "20191002";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:
 M5.update();
  if (M5.BtnA.isPressed()){
    M5.Lcd.setCursor(0,0);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.println("Starting Wi-Fi");
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
    }
    M5.Lcd.println("Connected");
    M5.Lcd.println(WiFi.localIP());
 
  }
  if (M5.BtnB.isPressed()){
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("Disconnecting Wi-Fi");
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    M5.Lcd.println("Wi-Fi Disconnected");

  }
}
