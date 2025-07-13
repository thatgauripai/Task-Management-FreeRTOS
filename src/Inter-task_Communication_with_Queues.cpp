#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#define QUEUE_LENGTH 5
#define PRODUCER_DELAY_MS 500
#define CONSUMER_DELAY_MS 1000

QueueHandle_t queue;
TaskHandle_t producerTaskHandle = NULL;
TaskHandle_t consumerTaskHandle = NULL;

void producerTask(void *pvParameters) {
    int counter = 0;
    while (1) {
        if (xQueueSend(queue, &counter, pdMS_TO_TICKS(100)) == pdPASS) {
            Serial.print("Producer: Sent ");
            Serial.println(counter);
            counter++;
        } else {
            Serial.println("Producer: Queue Full!");
        }
        vTaskDelay(pdMS_TO_TICKS(PRODUCER_DELAY_MS));
    }
}

void consumerTask(void *pvParameters) {
    int receivedValue;
    while (1) {
        if (xQueueReceive(queue, &receivedValue, pdMS_TO_TICKS(500)) == pdPASS) {
            Serial.print("Consumer: Received ");
            Serial.println(receivedValue);
        } else {
            Serial.println("Consumer: Queue Empty!");
        }
        vTaskDelay(pdMS_TO_TICKS(CONSUMER_DELAY_MS));
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Give Serial time to initialize

    Serial.println("\n=== FreeRTOS Queue Demo ===");

    queue = xQueueCreate(QUEUE_LENGTH, sizeof(int));
    if (queue == NULL) {
        Serial.println(" Failed to create queue!");
        while (1); // Stop if queue creation fails
    }

    // Create tasks with enough stack size for ESP32 (2048 words)
    xTaskCreate(producerTask, "Producer", 2048, NULL, 1, &producerTaskHandle);
    xTaskCreate(consumerTask, "Consumer", 2048, NULL, 1, &consumerTaskHandle);
}

void loop() {
    // Nothing here, tasks run independently
}
