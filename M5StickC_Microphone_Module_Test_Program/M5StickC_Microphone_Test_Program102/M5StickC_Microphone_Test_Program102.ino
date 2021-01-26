#include <M5StickC.h>
#include <driver/i2s.h>
 
#define htonl(x) ( ((x)<<24 &amp; 0xFF000000UL) | \
                   ((x)<< 8 &amp; 0x00FF0000UL) | \
                   ((x)>> 8 &amp; 0x0000FF00UL) | \
                   ((x)>>24 &amp; 0x000000FFUL) )
 
#define PIN_CLK  0
#define PIN_DATA 34
#define SAMPLING_RATE (44100/2)
#define READ_LEN (2 * 512)
#define SAVE_LEN (1024*100)
uint8_t READ_BUFFER[READ_LEN] = {0};
uint8_t SAVE_BUFFER[SAVE_LEN] = {0};
uint32_t savePos = 0;
bool recFlag = false;
 
uint16_t oldy[160];
int16_t *adcBuffer = NULL;
TaskHandle_t taskHandle;
size_t bytesread;
 
void i2sInit()
{
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
    .sample_rate =  SAMPLING_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
    .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = READ_LEN,
  };
 
  i2s_pin_config_t pin_config;
  pin_config.bck_io_num   = I2S_PIN_NO_CHANGE;
  pin_config.ws_io_num    = PIN_CLK;
  pin_config.data_out_num = I2S_PIN_NO_CHANGE;
  pin_config.data_in_num  = PIN_DATA;
 
  i2s_driver_install(I2S_NUM_0, &amp;i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &amp;pin_config);
  i2s_set_clk(I2S_NUM_0, SAMPLING_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
 

  recFlag = true;
  xTaskCreatePinnedToCore(mic_record_task, "mic_record_task", 2048, NULL, 1, &amp;taskHandle, 1);
}
 
void mic_record_task (void* arg)
{
  savePos = 0;
  memset(SAVE_BUFFER, 0, SAVE_LEN);
  while (recFlag) {
    i2s_read(I2S_NUM_0, (char*) READ_BUFFER, READ_LEN, &amp;bytesread, (100 / portTICK_RATE_MS));
    adcBuffer = (int16_t *)READ_BUFFER;
    showSignal();
    Serial.printf("bytesread = %d, SAVE_LEN=%d, savePos=%d\n", bytesread, SAVE_LEN, savePos);
    if ( (savePos + bytesread) < SAVE_LEN ) {
      memcpy( &amp;SAVE_BUFFER[savePos], READ_BUFFER, bytesread );
      savePos += bytesread;
    }
    vTaskDelay(1 / portTICK_RATE_MS);
  }
 

  vTaskDelete(NULL);
}
 
void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.println("mic");
}
 
 
void showSignal() {
  // Offset
  int32_t offset_sum = 0;
  for (int n = 0; n < 160; n++) {
    offset_sum += (int16_t)adcBuffer[n];
  }
  int offset_val = -( offset_sum / 160 );
 
  // Auto Gain
  int max_val = 200;
  for (int n = 0; n < 160; n++) {
    int16_t val = (int16_t)adcBuffer[n] + offset_val;
    if ( max_val < abs(val) ) {
      max_val = abs(val);
    }
  }
 
  int y;
  for (int n = 0; n < 160; n++) {
    y = adcBuffer[n] + offset_val;
    y = map(y, -max_val, max_val, 10, 70);
    M5.Lcd.drawPixel(n, oldy[n], WHITE);
    M5.Lcd.drawPixel(n, y, BLACK);
    oldy[n] = y;
  }
}
 
void loop() {
  M5.update();
 
  if ( M5.BtnA.wasPressed() ) {

    delay(200);
 
    // REC
    i2sInit();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("mic rec...");
    Serial.println("REC ON");
  } else if ( M5.BtnA.wasReleased() ) {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("mic       ");
    recFlag = false;
    delay(100); 
    Serial.println("REC OFF");
    Serial.printf("size=%d, sec=%1.1f\n", savePos, (double)savePos / (SAMPLING_RATE * 2));
 
    Serial.printf("52494646");                        
    Serial.printf("%08lx", htonl(savePos + 44 - 8));  
    Serial.printf("57415645");                        
    Serial.printf("666D7420");                        
    Serial.printf("10000000");                        
    Serial.printf("0100");                            
    Serial.printf("0100");                            
    Serial.printf("%08lx", htonl(SAMPLING_RATE));     
    Serial.printf("%08lx", htonl(SAMPLING_RATE * 2)); 
    Serial.printf("0200");                            
    Serial.printf("1000");                            
    Serial.printf("64617461");                        
    Serial.printf("%08lx", htonl(savePos));           
 
    for (int n = 0; n <= savePos; n++) {
      Serial.printf("%02x", SAVE_BUFFER[n]);
    }
    Serial.printf("\n");
  }
 
  delay(10);
}
