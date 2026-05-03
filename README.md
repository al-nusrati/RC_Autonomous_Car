
---

# 🦅 Project HAWK — RC Autonomous Car

**Course:** EC-310 Microprocessor & Microcontroller Based Design
**Institution:** NUST College of Electrical & Mechanical Engineering (CEME), Department of Computer Engineering
**Submitted to:** Prof. Ishfaq Hussain & Lab Engr. Usama Shokat
**Syndicate:** A & B | **Degree Batch:** 46

**Group Members:**
- Jawad Ahmed — 533047
- Shameen Bibi — 518113
- Rujman Majeed — 508713
- Areesha Nadeem — 503388

---

## Overview

Project HAWK is a fully autonomous RC car powered by an end-to-end deep neural network running entirely on a low-cost **ESP32-S3** microcontroller. It pushes the limits of bare-metal TinyML to achieve real-time AI steering with a target inference latency of **under 133ms**, fusing neural predictions with classical IMU-based yaw damping and ultrasonic obstacle avoidance — no cloud, no Linux SBC.

---

## Hardware

| Component | Role |
|---|---|
| ESP32-S3-WROOM-1 (16MB Flash, 8MB PSRAM) | Main compute unit |
| 7.4V Dual 18650 Li-ion Battery Pack | Power source |
| L298N Dual H-Bridge Motor Driver | Propulsion |
| TP4056 + LM2596 + AMS1117 | Power regulation & protection |
| MPU-6050 IMU | Yaw-rate damping |
| HC-SR04+ Ultrasonic Sensors (×3) | Zone-based obstacle avoidance |
| OV3660 / OV2640 Camera Module | Visual input for AI model |

---

## AI & TinyML Pipeline

- **Model:** MobileNetV2-0.35 with depthwise separable convolutions
- **Dataset:** Udacity self-driving dataset (augmented + class-balanced)
- **Input:** QQVGA (128×128) — 4× fewer pixels than QVGA for faster inference
- **Quantization:** Post-training INT8 → final `.tflite` model: **599KB**
- **Memory budget:** 600KB
- **Inference latency:** **40–60ms** (with hardware SIMD/PIE acceleration)
- **Training platform:** Kaggle (dual T4 GPUs)

---

## Firmware & RTOS

Built on **ESP-IDF + FreeRTOS** with deterministic dual-core task pinning:

- **Core 0:** Camera capture + live telemetry web dashboard (over ESP32 Access Point)
- **Core 1:** TFLite Micro inference + motor actuation

Critical model weights are pinned to internal SRAM to avoid PSRAM bus contention (which otherwise causes 15–20% latency variance).

---

## Software Stack

| Tool | Purpose |
|---|---|
| VS Code + ESP-IDF | Primary firmware development (C++) |
| Kaggle | Model training & INT8 quantization |
| Arduino IDE | Rapid hardware prototyping & debugging |
| GitHub | Version control for full pipeline |

---

## Repository

🔗 [https://github.com/al-nusrati/RC_Autonomous_Car.git](https://github.com/al-nusrati/RC_Autonomous_Car.git)

---

## Current Status

✅ Hardware chassis, power delivery, and sensor suite — fully assembled & verified 

✅ INT8 model compiled into 1MB firmware binary 

✅ FreeRTOS scheduler polling IMU and ultrasonic sensors 

✅ Live telemetry dashboard broadcasting over local AP 

⛔ **Blocker:** Defective OV3660 camera module (SCCB unresponsive) — awaiting replacement

**Next step:** Swap in a functional camera module → calibrate steering fusion → deploy on track.

---

## Conclusion

HAWK demonstrates that production-grade autonomous driving is achievable on a $5 microcontroller. By combining hardware SIMD acceleration, FreeRTOS determinism, and a heavily optimized TinyML pipeline, the system achieves 40–60ms end-to-end inference — proving that the future of embedded AI is **lean, deterministic, and edge-native**.
