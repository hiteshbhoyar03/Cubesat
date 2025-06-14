# 🌞 CubeSat Sun Sensor Board

<p align="center">
<img  width="39%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Sun%20Sensor/gallery/sunsensor%20front.png">
<img  width="39%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Sun%20Sensor/gallery/sunsensor%20back.png">
</p>

This Sun Sensor module is designed for fine sun vector detection on a CubeSat using position-sensitive detectors (PSDs). The sensor includes low-noise amplification, real-time processing via an ultra-low-power STM32 microcontroller, and SPI communication to the OBC or EPS.

> 🛰️ Part of a modular CubeSat system for attitude determination and control (ADCS) experiments and embedded systems learning.

---

## 🔧 Design Highlights

- 🌞 High-resolution, dual-axis sun vector sensing
- 🔍 Low-noise op-amp signal path
- ⚡ Ultra-low-power STM32 MCU for in-orbit efficiency
- 🔌 SPI-compatible with other CubeSat systems
- 🔒 Tri-state buffer to avoid SPI bus contention
- 🧩 Compact design for integration into small stacks

---

## 📦 Key Features

- **Hamamatsu S5990-01**
  - Dual-axis position-sensitive photodiodes (PSDs)
  - Analog voltage output proportional to light centroid

- **TLV9004Q1**
  - Quad-channel low-offset operational amplifiers
  - Used to amplify and condition the PSD outputs

- **STM32L031**
  - Ultra-low-power ARM Cortex-M0+ MCU
  - Handles sensor data acquisition, conversion, and SPI communication

- **SPI Interface**
  - Communicates with the main CubeSat controller (e.g., OBC)
  - Uses **SN74LVC1G125DBVT** buffer to manage the MISO line (high-impedance when inactive)

- **Connector**
  - Compact Molex connector for external interface to the CubeSat stack (power + SPI)

---

## 📐 Functional Overview

| Component                   | Function                                      |
|-----------------------------|-----------------------------------------------|
| `S5990-01` (x2)             | Sun vector detection via PSD                  |
| `TLV9004Q` (x2)             | Signal amplification and filtering            |
| `STM32L031`                 | Data acquisition and digital SPI conversion   |
| `SN74LVC1G125`              | Tri-state buffer for SPI MISO line control    |
| `503763-0691`               | Interface connector for power + SPI signals   |

---

## 🔧 Tools Used

- 🛠 **Altium Designer** – Schematic and PCB Layout  
- 🔌 **STM32CubeIDE** – Embedded development
- 🔌 **STM32CubeMX** – Peripheral and clock config  
- 📦 **GitHub** – VersVersion control , documentation and project showcase

---

## 👤 Author

**Hitesh Bhoyar**  
📍 Embedded Systems | CubeSat Design | Low Power Electronics  
[GitHub →](https://github.com/hiteshbhoyar03)
> For educational use. Feel free to fork, reuse, or reach out if you are exploring embedded systems!

---

> 📦 Visit the [main repository](https://github.com/hiteshbhoyar03/Cubesat-master) for other subsystems.

## 📜 License

Part of the [CubeSat Master Project](https://github.com/hiteshbhoyar03/Cubesat-master)  
Licensed under the [MIT License](../LICENSE)

---
