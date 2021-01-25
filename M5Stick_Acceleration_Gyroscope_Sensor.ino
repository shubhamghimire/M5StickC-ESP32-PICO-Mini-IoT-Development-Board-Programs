#include <M5StickC.h>

 
int16_t accX = 0;
int16_t accY = 0;
int16_t accZ = 0;
 
int16_t gyroX = 0;
int16_t gyroY = 0;
int16_t gyroZ = 0;
 
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("SH200I TEST");
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.println("  X       Y       Z");
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
}
 
float max_gyroX = 0;
float min_gyroX = 0;
float max_gyroY = 0;
float min_gyroY = 0;
float max_gyroZ = 0;
float min_gyroZ = 0;
 
float max_accX = 0;
float min_accX = 0;
float max_accY = 0;
float min_accY = 0;
float max_accZ = 0;
float min_accZ = 0;
 
void loop() {
  if (digitalRead(M5_BUTTON_HOME) == LOW || digitalRead(M5_BUTTON_RST) == LOW ) {
    max_gyroX = 0;
    min_gyroX = 0;
    max_gyroY = 0;
    min_gyroY = 0;
    max_gyroZ = 0;
    min_gyroZ = 0;
 
    max_accX = 0;
    min_accX = 0;
    max_accY = 0;
    min_accY = 0;
    max_accZ = 0;
    min_accZ = 0;
    delay(1000);
  }
 
  // put your main code here, to run repeatedly:
  M5.IMU.getGyroData('&amp';gyroX, '&amp';gyroY, '&amp';gyroZ);
  M5.IMU.getAccelData('&amp';accX, '&amp';accY, '&amp';accZ);
 
  if ( max_gyroX < ((float) gyroX) * M5.IMU.gRes ) {
    max_gyroX = ((float) gyroX) * M5.IMU.gRes;
  }
  if ( ((float) gyroX) * M5.IMU.gRes < min_gyroX ) {
    min_gyroX = ((float) gyroX) * M5.IMU.gRes;
  }
 
  if ( max_gyroY < ((float) gyroY) * M5.IMU.gRes ) {
    max_gyroY = ((float) gyroY) * M5.IMU.gRes;
  }
  if ( ((float) gyroY) * M5.IMU.gRes < min_gyroY ) {
    min_gyroY = ((float) gyroY) * M5.IMU.gRes;
  }
 
  if ( max_gyroZ < ((float) gyroZ) * M5.IMU.gRes ) {
    max_gyroZ = ((float) gyroZ) * M5.IMU.gRes;
  }
  if ( ((float) gyroZ) * M5.IMU.gRes < min_gyroZ ) {
    min_gyroZ = ((float) gyroZ) * M5.IMU.gRes;
  }
 
  if ( max_accX < ((float) accX) * M5.IMU.aRes ) {
    max_accX = ((float) accX) * M5.IMU.aRes;
  }
  if ( ((float) accX) * M5.IMU.aRes < min_accX ) {
    min_accX = ((float) accX) * M5.IMU.aRes;
  }
 
  if ( max_accY < ((float) accY) * M5.IMU.aRes ) {
    max_accY = ((float) accY) * M5.IMU.aRes;
  }
  if ( ((float) accY) * M5.IMU.aRes < min_accY ) {
    min_accY = ((float) accY) * M5.IMU.aRes;
  }
 
  if ( max_accZ < ((float) accZ) * M5.IMU.aRes ) {
    max_accZ = ((float) accZ) * M5.IMU.aRes;
  }
  if ( ((float) accZ) * M5.IMU.aRes < min_accZ ) {
    min_accZ = ((float) accZ) * M5.IMU.aRes;
  }
 
  M5.Lcd.setCursor(0, 24);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", ((float) gyroX) * M5.IMU.gRes, ((float) gyroY) * M5.IMU.gRes, ((float) gyroZ) * M5.IMU.gRes);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", max_gyroX, max_gyroY, max_gyroZ);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", min_gyroX, min_gyroY, min_gyroZ);
 
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", ((float) accX) * M5.IMU.aRes, ((float) accY) * M5.IMU.aRes, ((float) accZ) * M5.IMU.aRes);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", max_accX, max_accY, max_accZ);
  M5.Lcd.printf("%+7.2f %+7.2f %+7.2f\n", min_accX, min_accY, min_accZ);
}
