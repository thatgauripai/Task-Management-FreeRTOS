#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Task Handles
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

// Task 1 - Simple counter with stack monitoring
void task1(void *pvParameters) {
  int counter = 0;
  while (1) {
    counter++;

    UBaseType_t stackRemaining = uxTaskGetStackHighWaterMark(NULL);

    Serial.printf("[Task1] Counter: %d | Stack remaining: %u bytes\n",
                  counter,
                  stackRemaining * sizeof(StackType_t));

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Task 2 - Memory intensive task
void task2(void *pvParameters) {
  float data[20]; // Consumes stack space

  while (1) {
    for (int i = 0; i < 20; i++) {
      data[i] = sin(i * 0.1f);
    }

    UBaseType_t stackRemaining = uxTaskGetStackHighWaterMark(NULL);

    Serial.printf("[Task2] Stack remaining: %u bytes\n",
                  stackRemaining * sizeof(StackType_t));

    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Give time for Serial to connect

  Serial.println("\n=== Task Stack Monitoring Demo ===");

  // Create tasks with custom stack sizes
  xTaskCreate(
      task1,
      "CounterTask",
      2048,      // Stack size in words
      NULL,
      1,
      &task1Handle);

  xTaskCreate(
      task2,
      "MemoryTask",
      2048,      // Stack size in words
      NULL,
      1,
      &task2Handle);
}

void loop() {
  // FreeRTOS loop unused
}

// Optional: Stack overflow handler
extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  Serial.printf("\nCRITICAL: Stack overflow in task %s!\n", pcTaskName);
  pinMode(2, OUTPUT);

  while (1) {
    digitalWrite(2, !digitalRead(2));
    delay(100);
  }
}
