#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t producerHandle = NULL;
TaskHandle_t consumerHandle = NULL;

void consumerTask(void *pvParameters) {
  uint32_t notificationCount = 0;

  while (1) {
    // Wait for notification
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    
    if (ulNotificationValue > 0) {
      Serial.printf("[Consumer] Received notification %u\n", ++notificationCount);
    }

    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void producerTask(void *pvParameters) {
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Notify the consumer task
    xTaskNotifyGive(consumerHandle);
    Serial.println("[Producer] Sent notification");
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);  // Let Serial initialize

  // Create tasks with sufficient stack
  xTaskCreate(consumerTask, "Consumer", 2048, NULL, 2, &consumerHandle);
  xTaskCreate(producerTask, "Producer", 2048, NULL, 1, &producerHandle);
}

void loop() {
  // Nothing here – FreeRTOS is managing the tasks
}
