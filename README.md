# STM32 Ultrasonic Intrusion Detection System 🛡️

## 📝 Overview
This project implements a real-time obstacle detection and intrusion alert system using an **STM32 microcontroller** and an **HC-SRF05 ultrasonic sensor**. The system dynamically maps the position of approaching objects on a **128x160 TFT display** and triggers automated hardware/software alerts when an object crosses a critical threshold.

## ✨ Key Features
* **Real-time Distance Measurement:** Accurately measures object distance up to 10 cm.
* **Dynamic GUI Mapping:** Real-time visual representation on a 128x160 TFT screen, divided into "Safe Zone" and "Intrusion Zone".
* **Double Alert Mechanism:** * When an object is detected at a distance of **< 5 cm** (Critical Threshold), the system triggers:
    1. **Software Alert:** The marker on the TFT display turns black.
    2. **Hardware Alert:** An external warning LED is illuminated.

## 🛠️ Hardware Requirements
* **Microcontroller:** STM32 (e.g., STM32F4xx / STM32F1xx - *Update your specific board here*)
* **Sensor:** HC-SRF05 Ultrasonic Distance Sensor
* **Display:** TFT Display (128x160 pixels, e.g., ST7735 or similar SPI display)
* **Other Components:** LED, Resistors, Jumper wires, Breadboard

## ⚙️ System Logic
1. The **STM32** sends a trigger pulse to the **HC-SRF05**.
2. The sensor calculates the time-of-flight of the ultrasonic echo and returns a pulse.
3. The microcontroller calculates the precise distance.
4. If `Distance > 5 cm`: The TFT screen displays the object in the Safe Zone. The LED remains off.
5. If `Distance <= 5 cm`: The object enters the Intrusion Zone. The TFT marker switches to black, and the warning LED turns ON instantly.

## 🚀 Setup and Pin Wiring
*(Tip: Update this table with the actual pins you used on your STM32)*

| Component | Pin | STM32 Pin |
| :--- | :--- | :--- |
| **HC-SRF05** | VCC | 5V |
| | GND | GND |
| | TRIG | PAx (Example) |
| | ECHO | PAy (Example) |
| **TFT 128x160** | CS, RESET, SDA, SCL | SPI Pins (e.g., PA5, PA7...) |
| **LED Alert** | Anode (+) | PBx (Example) |

## 💻 Software & Tools Used
* C/C++ (Bare-metal / HAL Library)
* STM32CubeIDE
