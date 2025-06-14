# 🔋 CubeSat Battery Board

<p align="center">
<img  width="39%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Battery%20Board/gallery/battery%20board%20front.png">
<img  width="39%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Battery%20Board/gallery/battery%20board%20back.png">
</p>

This is the CubeSat Battery Board designed to provide stable, rechargeable power to the system via regulated Li-ion cell management. Built around high-efficiency battery charging ICs and ideal diode power path controllers, this board ensures safe and reliable power delivery to the Electrical Power System (EPS) and other subsystems.

It handles solar power input, charging, and provides regulated power output to the Electrical Power System (EPS) through a IPS1-105-01-L-D interface.

> 🛰️ This board is part of a modular, learning-focused CubeSat design aimed at developing embedded hardware skills in space-grade power management.

---

## 🧪 Functional Highlights

- 🔋 Independent charging of up to 4 Li-ion cells
- 🌡️ Temperature-aware charging with 4 × NTCs
- ☀️ Solar power input with voltage-protected output
- 🔀 Ideal diode switchover and load sharing
- 📦 Compatible with CubeSat PC104 mechanical/electrical spec

---

## 📦 Key Features


- **LTC4085-4 Battery Chargers**
  - High-efficiency 4.0V Li-ion chargers with PowerPath control
  - Integrated thermal regulation, current limiting, USB OTG
  - **NTC thermistors** connected to each charger for thermal feedback and safety

- **LTC4415 Ideal Diode Controllers**
  - Power path protection and current sharing
  - Prevents backfeeding and supports seamless source switching

- **Solar Power Input**
  - Connector: `IPS1-105-01-L-D-VS`
  - Accepts solar panel power input
  - Also provides main power output to the EPS system

- **Standard PC104 Interface**
  - Connects to CubeSat stack

- **4 × Keystone 54 18650 Battery Holders**
  - Secure, spring-loaded battery mounts

---

## ⚙️ Power Flow Overview

### 🔋 Inputs & Outputs

| Interface              | Function                                             |
|------------------------|------------------------------------------------------|
| `IPS1-105-01-L-D-VS`   | Solar panel input + output to EPS                    |
| `PC104`                | Stackable connection to EPS and other subsystems     |
| `4 × Battery Holders`  | Rechargeable Li-ion storage for 18650 cells          |
| `4 × NTC`              | Thermal sensing for battery safety with LTC4085-4    |

### 🔌 Power Management Components

| Component                  | Function                                         |
|----------------------------|--------------------------------------------------|
| `LTC4085-4` (×4)           | Li-ion battery charger with USB PowerPath        |
| `LTC4415` (×2)             | Ideal diode ORing controller for power paths     |
| `NTC Thermistors` (×4)     | Overtemperature monitoring and regulation input  |

---

## 🧰 Hardware Design Goals

- Modular battery-backed power for EPS and other CubeSat boards
- Safe charging with active thermal regulation (via NTCs)
- Input/output Power switching using ideal diodes
- Solar power integration via a compact connector
- Clean and stackable via PC104

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
