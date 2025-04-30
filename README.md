# Smart Walking Stick for Elderly 👨‍🦯 
A life-saving assistive device that detects falls, monitors vital signs, and sends real-time alerts with GPS location to caregivers — all powered by ESP8266 and smart sensors.

---

## 🔍 Overview

The **Smart Walking Stick** is a compact, affordable, and real-time health monitoring system designed especially for elderly individuals. It continuously monitors **movement**, **falls**, **pulse rate**, **SpO₂**, and **location**, triggering alerts and sharing coordinates if abnormalities are detected.

---

## 🚀 Tech Stack

| Technology | Logo |
|------------|------|
| **Embedded C++** | ![Embedded C++](https://img.shields.io/badge/C%2B%2B-Embedded-informational?logo=c%2B%2B&logoColor=white&color=blue) |
| **Python** | ![Python](https://img.shields.io/badge/Python-3.x-blue?logo=python&logoColor=white) |
| **MicroPython** | ![MicroPython](https://img.shields.io/badge/MicroPython-Firmware-brightgreen?logo=python&logoColor=white) |
| **TinyML** | ![TinyML](https://img.shields.io/badge/TinyML-Edge%20AI-orange?logo=tensorflow&logoColor=white) |
| **TensorFlow** | ![TensorFlow](https://img.shields.io/badge/TensorFlow-Model-informational?logo=tensorflow&logoColor=white&color=ff6f00) |
| **Keras** | ![Keras](https://img.shields.io/badge/Keras-Neural%20Nets-red?logo=keras&logoColor=white) |

> *(Used for pre-trained activity classification model and signal processing logic.)*

---

## 📦 Features

✅ **Fall Detection** using MPU6050  
✅ **No-Movement Monitoring** to detect unconsciousness  
✅ **Pulse & SpO₂ Sensing** via MAX30102  
✅ **GPS Location Tracking** with Neo-6M  
✅ **Alert System** using buzzer and LED  
✅ **Emergency Notification** with live coordinates  
✅ **Low Power & Compact Design**

---

## 🧠 How It Works

- **MPU6050**: Detects falls or unusual motion (X-axis is faulty, Y/Z axes used)  
- **MAX30102**: Monitors pulse rate and SpO₂  
- **Neo-6M GPS**: Tracks live location  
- **ESP8266**: Controls the logic and communication  
- **LED + Buzzer**: Provides instant alerts locally

---

## 🛠️ Hardware Used

| Component        | Description                          |
|------------------|--------------------------------------|
| ESP8266 (NodeMCU) | Wi-Fi microcontroller               |
| MPU6050          | 3-axis Accelerometer + Gyroscope     |
| MAX30102         | Pulse & SpO₂ sensor                  |
| Neo-6M GPS       | GPS Module for tracking              |
| Buzzer + LED     | Local alert system                   |
| 18650 Battery    | Power source                         |

---

## 📁 Folder Structure

```
📂 SmartWalkingStick
├── 📄 README.md
├── 📁 src/
│   ├── main.ino         # Arduino code for ESP8266
│   └── model.tflite     # TensorFlow Lite model for motion detection
├── 📁 docs/
│   └── schematic.pdf    # Circuit Diagram
└── 📁 assets/
    └── demo.gif         # Demo visuals
```

---

## 🧪 Status

- ✅ Fall & No-Movement Detection  
- ✅ Pulse/SpO₂ alert trigger  
- ✅ LED/Buzzer functional  
- 🔄 GPS coordinate transmission in progress  
- 🔜 Integration with IoT dashboard / SMS / email alert

---

## 🤝 Contributors

- **Dhrubo Ghosh** — Embedded Systems, Machine Learning, Firmware, and System Logic  
- **Arya Das** — Machine Learning, Algorithms , Problem Solving

---
