# Smart Walking Stick for Elderly 👨‍🦯 
A life-saving assistive device that detects falls, monitors vital signs, and sends real-time alerts with GPS location to caregivers — all powered by ESP8266 and smart sensors.

---

## 🔍 Overview

The **Smart Walking Stick** is a compact, affordable, and real-time health monitoring system designed especially for elderly individuals. It continuously monitors **movement**, **falls**, **pulse rate**, **SpO₂**, and **location**, triggering alerts and sharing coordinates if abnormalities are detected.

---

🚀 Tech Stack
<p align="center"> <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg" alt="Embedded C++" height="50"/> &nbsp;&nbsp;&nbsp; <img src="https://www.vectorlogo.zone/logos/python/python-horizontal.svg" alt="Python" height="50"/> &nbsp;&nbsp;&nbsp; <img src="https://micropython.org/static/img/micropython-logo.png" alt="MicroPython" height="50"/> &nbsp;&nbsp;&nbsp; <img src="https://upload.wikimedia.org/wikipedia/commons/7/7c/Edge_AI_logo.png" alt="Edge AI" height="50"/> &nbsp;&nbsp;&nbsp; <img src="https://www.vectorlogo.zone/logos/tensorflow/tensorflow-icon.svg" alt="TensorFlow" height="50"/> &nbsp;&nbsp;&nbsp; <img src="https://upload.wikimedia.org/wikipedia/commons/a/ae/Keras_logo.svg" alt="Keras" height="50"/> </p>

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

🛠️ Hardware Used

Component	Description
ESP8266	Wi-Fi microcontroller (NodeMCU board)
MPU6050	3-axis Accelerometer + Gyroscope
MAX30102	Pulse & SpO₂ sensor
Neo-6M GPS	GPS Module for real-time tracking
Laser Module	Laser emitter for obstacle awareness / direction indicator
Buzzer + LED	Local alert and status indication
Rechargeable Battery	Power source for portability and reuse

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
