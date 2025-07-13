#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Task handles
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

// Task1: Simulates state transitions
void Task_Manager(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        Serial.println("Task1: Ready state");

        // Enter Blocked state
        Serial.println("Task1: Entering Blocked state for 2s...");
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Enter Suspended state
        Serial.println("Task1: Entering Suspended state...");
        vTaskSuspend(NULL);  // Suspends itself

        // Will resume from here after vTaskResume
        Serial.println("Task1: Resumed and running again...");
    }
}

// Task2: Resumes Task1 after a delay
void Task_Controller(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        Serial.println("Task2: Delaying 4s before resuming Task1...");
        vTaskDelay(pdMS_TO_TICKS(4000));

        Serial.println("Task2: Resuming Task1...");
        if (Task1Handle != NULL) {
            vTaskResume(Task1Handle);
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // Allow Serial to initialize

    Serial.println("FreeRTOS Task State Transition Example");

    // Create Task1
    xTaskCreate(Task_Manager, "Task1", 2048, NULL, 1, &Task1Handle);

    // Create Task2
    xTaskCreate(Task_Controller, "Task2", 2048, NULL, 1, &Task2Handle);

    // ✅ No need to start scheduler — handled automatically in Arduino
}

void loop() {
    // Nothing here — FreeRTOS manages everything
}
