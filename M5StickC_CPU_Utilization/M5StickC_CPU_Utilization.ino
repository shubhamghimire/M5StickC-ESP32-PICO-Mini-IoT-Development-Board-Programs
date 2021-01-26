#include "esp_freertos_hooks.h"

TaskHandle_t taskHandle[2];

long core0IdleCount = 0;
long core0TickCount = 0;
long core1IdleCount = 0;
long core1TickCount = 0;

void testTask(void *pvParameters){
  while(1){
    delayMicroseconds(random(1, 500000));
    delay(random(1, 500));
    
  }
}

bool core0IdleHook(void){
  core0IdleCount++;
  return true;
  
}

void core0TickHook(void){
  core0TickCount++;
}

bool core1IdleHook(void){
  core1IdleCount++;
  return true;
}

bool core1TickHook(void){
  core1TickCount++;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  esp_register_freertos_idle_hook_for_cpu(&amp;core0IdleHook, 0);
  esp_register_freertos_tick_hook_for_cpu(&amp;core0TickHook, 0);
  esp_register_freertos_idle_hook_for_cpu(&amp;core1IdleHook, 1);
  esp_register_freertos_idle_hook_for_cpu(&amp;core1TickHook, 1);

  xTaskCreateUniversal(
    testTask,
    "testTask1",
    8192,
    NULL,
    1,
    &amp;taskHandle[0],
    0
   );

   xTaskCreateUniversal(
    testTask,
    "testTask2",
    8192,
    NULL,
    1,
    &amp;taskHandle[1];
    1
   );

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("=============================================================\n");
  Serial.printf("core0IdleCount = %71d, core0TickCount = %71d, Idle = %5.1f %%\n", core0IdleCount, core0TickCount, core0IdleCount * 100.0 / core0TickCount);
  Serial.printf("core1IdleCount = %71d, core1TickCount = %71d, Idle = %5.1f %%\n", core1IdleCount, core1TickCount, core1IdleCount * 100.0 / core1TickCount);

  core0IdleCount = 0;
  core0TickCount = 0;
  core1IdleCount = 0;
  core1TickCount = 0;

  delay(2000);
  

}
