#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// Define mutex 
SemaphoreHandle_t resourceMutex;

void LowPriorityTask(void *pvParameters) {
    while (1) {
        Serial.println("Low-Priority Task: Working before taking resource.");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Take the mutex with priority inheritance
        if (xSemaphoreTake(resourceMutex, portMAX_DELAY) == pdTRUE) {
            Serial.println("Low-Priority Task: Holding resource.");
            vTaskDelay(pdMS_TO_TICKS(3000));
            Serial.println("Low-Priority Task: Releasing resource.");
            xSemaphoreGive(resourceMutex);
        }
    }
}

void HighPriorityTask(void *pvParameters) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1500)); 
        Serial.println("High-Priority Task: Waiting for resource.");

        if (xSemaphoreTake(resourceMutex, portMAX_DELAY) == pdTRUE) {
            Serial.println("High-Priority Task: Acquired resource!");
            vTaskDelay(pdMS_TO_TICKS(500));
            Serial.println("High-Priority Task: Released resource.");
            xSemaphoreGive(resourceMutex);
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Give time for Serial to connect

    // Create mutex with priority inheritance
    resourceMutex = xSemaphoreCreateMutex();
    if (resourceMutex == NULL) {
        Serial.println("Mutex creation failed!");
        while (1);
    }

    // Create tasks
    xTaskCreate(LowPriorityTask, "LowPrio", 2048, NULL, 1, NULL);
    xTaskCreate(HighPriorityTask, "HighPrio", 2048, NULL, 2, NULL);

    // No need to call vTaskStartScheduler()
}

void loop() {
    // Not used in FreeRTOS, keep empty
}
