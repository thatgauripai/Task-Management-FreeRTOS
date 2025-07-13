#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Optional: Track how many times idle hook is called
volatile uint32_t idleCounter = 0;

// Task functions
void Task1(void *pvParameters);
void Task2(void *pvParameters);

void setup() {
  Serial.begin(115200);
  delay(2000);  // Allow time for Serial to connect
  Serial.println("ESP32 FreeRTOS Idle Hook Example");

  // Create tasks with appropriate stack size
  xTaskCreate(Task1, "Task1", 2048, NULL, 2, NULL);
  xTaskCreate(Task2, "Task2", 2048, NULL, 2, NULL);
}

void loop() {
  // Not used in FreeRTOS
}

void Task1(void *pvParameters) {
  while (1) {
    Serial.println("Task 1 is running");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void Task2(void *pvParameters) {
  while (1) {
    Serial.println("Task 2 is running");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Idle hook function (called when no other task is running)
extern "C" void vApplicationIdleHook(void) {
  idleCounter++;
  if (idleCounter % 100000 == 0) {
    Serial.println("[Idle Hook] CPU is idle");
  }
}
