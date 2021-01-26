#define QUEUE_LENGTH 4

QueueHandle_t xQueue;

QueueHandle_t xQueueMailbox;

void setup() {
  // put your setup code here, to run once:

  uint8_t data = 1;

  Serial.begin(115200);
  Serial.println("Queue Test");

  xQueue = xQueueCreate(QUEUE_LENGTH, sizeof(uint8_t));

  xQueueMailbox = xQueueCreate(1, sizeof(uint8_t));

  xQueueSend(xQueue, //&amp;data, 0);
  data++;

  xQueueSendToFront(xQueue, &amp;data, 0);
  data++;

  xQueueSendToBack(xQueue, &amp;data, 0);
  data++

  xQueueOverwrite(xQueueMailbox, &amp;data);
  data++;

  xQueueOverwrite(xQueueMailbox, &amp;data);
  data++;


  Serial.printf("uxQueueMessagesWaiting = %d\n", uxQueueMessagesWaiting(xQueue));
  Serial.printf("uxQueueSpacesAvailable = %d\n", uxQueueSpacesAvailable(xQueue));

  Serial.printf("xQueueIsQueueEmptyFromISR = %d\n", xQueueIsQueueEmptyFromISR(xQueue));
  Serial.printf("xQueueIsQueueFullFromISR = %d\n", xQueueIsQueueFullFromISR(xQueue));
  Serial.printf("uxQueueMessagesWaitingFromISR = %d\n", uxQueueMessagesWaitingFromISR(xQueue));

  Serial.println("Peek Test");
  xQueuePeek(xQueue, &amp;data, 0);
  Serial.println(data);
  xQueuePeek(xQueue, &amp;data, 0);
  Serial.println(data);


  int ret;
  Serial.println("Receive Test");
  
  ret = xQueueReceive(xQueue, &amp;data, 0);
  Serial.printf("ret = %d, data = %d\n", ret, data);

  ret = xQueueReceive(xQueue, &amp;data, 0);
  Serial.printf("ret = %d, data = %d\n", ret, data);

  ret = xQueueReceive(xQueue, &amp;data, 0);
  Serial.printf("ret = %d, data = %d\n", ret, data);

  ret = xQueueReceive(xQueue, &amp;data, 0);
  Serial.printf("ret = %d, data = %d\n", ret, data);
  
  ret = xQueueReceive(xQueue, &amp;data, 0);
  Serial.printf("ret = %d, data = %d\n", ret, data);

  Serial.println("Mailbox Test");
  xQueuePeek(xQueueMailbox, &amp;data, 0);
  Serial.println(data);

  Serial.println("xQueueReset Test");
  xQueueReset(xQueue);
  xQueueReset(xQueueMailbox);

  Serial.println("QueueSet Test");
  QueueSetHandle_t xQueueSet;
  xQueueSet = xQueueCreateSet(QUEUE_LENGTH + 1);
  xQueueAddToSet(xQueue, xQueueSet);
  xQueueAddToSet(xQueueMailbox, xQueueSet);

  data = 100;
  xQueueSend(xQueue, &amp;data, 0);
  data++;
  xQueueSend(xQueue, &amp;data,0);
  data++;
  xQueueSend(xQueueMailbox, &amp;data, 0);
  
  
  while(1){

    QueueHandle_t queue = xQueueSelectFromSet(xQueueSet, 0);
    if(queue == NULL){
      break;
    }

    if(queue == xQueue){
      Serial,print("xQueue ");
      
    }
    else if(queue = xQueueMailbox){
      Serial.print("xQueueMailbox ");
    }
    else{
      Serial.print("? ");
    }

    ret = xQueueReceive(queue, &amp;data, 0);
    Serial.printf("ret = %d, data = %d\n", ret, data);
  }

  vQueueDelete(xQueue);
  vQueueDelete(xQueueMailbox);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
