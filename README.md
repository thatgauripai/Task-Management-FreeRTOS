# 🚀 FreeRTOS Task Management on ESP32

This repository contains a collection of hands-on exercises designed to explore **task management features in FreeRTOS**, using the ESP32 and the Arduino framework via PlatformIO.

---

## 📘 What This Project Covers

| ID  | Feature                             | Description |
|-----|-------------------------------------|-------------|
| 5️⃣ | Task State Transitions              | Simulates transitions: Ready → Blocked → Suspended → Resumed |
| 6️⃣ | Idle Task Hook                      | Tracks idle time using `vApplicationIdleHook()` |
| 7️⃣ | Task Notifications                  | Lightweight inter-task communication using `xTaskNotifyGive()` |
| 8️⃣ | Queues                              | Producer-consumer model using `xQueueSend()` and `xQueueReceive()` |
| 🔟 | Stack Monitoring                     | Uses `uxTaskGetStackHighWaterMark()` for memory optimization |
| 1️⃣2️⃣ | Priority Inversion & Mutex           | Demonstrates priority inheritance with mutexes |

---

## 🛠️ Platform

- **Board**: ESP32 Dev Module
- **Framework**: Arduino + FreeRTOS (PlatformIO)
- **IDE**: Visual Studio Code with PlatformIO extension

---

## 🧪 Folder Structure

# Task-Management-FreeRTOS
