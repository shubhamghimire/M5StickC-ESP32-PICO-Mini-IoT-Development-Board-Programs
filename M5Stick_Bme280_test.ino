#include <M5StickC.h>  // ----A


#include <Wire.h>

#include <Adafruit_Sensor.h>

#include <Adafruit_BME280.h>





Adafruit_BME280 bme;



void setup() {

    M5.begin();
    Serial.begin(115200);
    M5.Axp.ScreenBreath(10);    // 画面の輝度を少し下げる ----B

    M5.Lcd.setRotation(3);      // 左を上にする         ----C

    M5.Lcd.setTextSize(2);      // 文字サイズを2にする

    M5.Lcd.fillScreen(BLACK);   // 背景を黒にする



    Wire.begin();               // I2Cを初期化する

    while (!bme.begin(0x76)) {  // BMP280を初期化する

        M5.Lcd.println("BME280 init fail");

    }

}



void loop() {

    float tmp = bme.readTemperature();

    float hum = bme.readHumidity();

    float pressure = bme.readPressure();

    



    M5.Lcd.setCursor(0, 0, 1);

    M5.Lcd.printf("temp: %4.1f'C\r\n", tmp);
    Serial.println(tmp);
    M5.Lcd.printf("humid:%4.1f%%\r\n", hum);
    Serial.println(hum);
    M5.Lcd.printf("press:%4.0fhPa\r\n", pressure / 100);

 

    delay(10 * 1000);

}
