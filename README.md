# 🛰️ CubeSat Master Project

![Repo Size](https://img.shields.io/github/repo-size/hiteshbhoyar03/Cubesat-master)
![Last Commit](https://img.shields.io/github/last-commit/hiteshbhoyar03/Cubesat-master)
![License](https://img.shields.io/github/license/hiteshbhoyar03/Cubesat-master)
![GitHub stars](https://img.shields.io/github/stars/hiteshbhoyar03/Cubesat-master?style=social)

---
<p align="center">
<img  width="25%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/OnBoard%20Computer_OBC/gallery/obc%20front.png">
<img  width="25%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Electrical%20Power%20System_EPS/gallery/EPS_v1%20front.png">
<img  width="25%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Battery%20Board/gallery/battery%20board%20front.png">
<img  width="19%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Sun%20Sensor/gallery/sunsensor%20front.png">
</p>

A open-source CubeSat project featuring fully designed schematic and PCB layouts, focused on essential subsystems: Onboard Computer (OBC), Electrical Power System (EPS), Battery Management, and a custom SPI-based Sun Sensor.  Designed as a **learning and portfolio project**, this CubeSat stack includes:

- 🧠 Onboard Computer (OBC)
- 🔋 Electrical Power System (EPS)
- ⚡ Battery Board
- 🌞 Sun Sensor Board

This CubeSat project aims to demonstrate a complete electronic subsystem stack suitable for academic learning purpose.

> ✅ Hardware (schematics, layout, stack interface) is complete and ready.  
> 🔧 Firmware development is in progress using STM32CubeIDE and STM32CubeMX.

---

## 🧠 Onboard Computer (OBC)

<a href="https://github.com/hiteshbhoyar03/Cubesat-master/tree/main/OnBoard%20Computer_OBC">
<img align="right" width="30%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/OnBoard%20Computer_OBC/gallery/obc%20front.png">
</a>

The brain of the CubeSat, responsible for mission control, data handling, and system coordination. It interfaces with various sensors (IMU, magnetometer, GPS, Sun Sensor) and memory units (MRAM, NOR Flash) to perform autonomous decision-making and telemetry. It also communicates with the EPS and other modules using CAN and UART.

- **Processor**: STM32L496ZGT6 
- **Memory**: MR25H40MDF (MRAM), S25HL512TFANHI010 (NOR Flash)
- **Sensors**: ISM330ISN (IMU), MMC5983MA (Magnetometer)

📂 [View OBC Design]( OnBoard Computer_OBC/ )

---

## 🔋 Electrical Power System (EPS)

<a href="https://github.com/hiteshbhoyar03/Cubesat-master/tree/main/Electrical%20Power%20System_EPS">
<img align="right" width="30%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Electrical%20Power%20System_EPS/gallery/EPS_v1%20front.png">
</a>

The power distribution and management unit of the CubeSat. It regulates and switches multiple power rails (3.3V, 5V, unregulated), monitors solar input and battery status, and ensures safe and efficient power flow throughout the system. It features a dual-MCU architecture for redundancy, MPPT solar charging, temperature monitoring, heater control, and full CAN/UART communication.

- **Main MCU**: STM32L496
- **Standby/Reset MCU**: STM32L452 (SRIC)
- Designed with minimal power usage for deep sleep and wakeup control

  📂 [View EPS Design]( Electrical Power System_EPS/ )

---

## ⚡ Battery Board

<a href="https://github.com/hiteshbhoyar03/Cubesat-master/tree/main/Battery%20Board">
<img align="right" width="30%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Battery%20Board/gallery/battery%20board%20front.png">
</a>

The CubeSat’s energy storage subsystem, holding four 18650 Li-Ion cells. It handles charging, protection, and power delivery to the EPS via ideal diode controllers. The board includes thermal monitoring for safety and interfaces with the solar panels and EPS through dedicated connectors.

- **Battery Holders**: 4 × 18650
- **Chargers**: 4 × LTC4085EDE-4#PBF
- **Power Muxing**: 2 × LTC4415IDHC#TRPBF ideal diode controllers
- **NTCs**: 4 × NTCs for charger temperature feedback
- **Connectors**:
  - Solar power input: IPS1-105-01-L-D-VS

📂 [View Battery Board Design]( Battery Board/ )

---

## 🌞 Sun Sensor Board

<a href="https://github.com/hiteshbhoyar03/Cubesat-master/tree/main/Sun%20Sensor">
<img align="right" width="22%" src="https://github.com/hiteshbhoyar03/Cubesat-master/blob/main/Sun%20Sensor/gallery/sunsensor%20front.png">
</a>

A lightweight attitude reference sensor using dual analog PSDs to measure the direction of sunlight. It processes analog outputs via op-amps and converts them to digital values using an ultra-low-power STM32 MCU. It transmits sun vector data to the OBC over an SPI interface and supports MISO tri-state control for shared bus compatibility.

- **MCU**: STM32L031G6U7
- **PSD Sensors**: 2 × Hamamatsu S5990-01
- **Signal Conditioning**: 2 × TLV9004Q1 (quad op-amps)
- **Interface**: SPI with MISO 

📂 [View Sun Sensor Design]( Sun Sensor/ )

---

## 🧪 Project Status

- [x] Hardware schematics and layout complete
- [x] Stack connector interface aligned (PC104)
- [x] Sun Sensor and Power testing underway
- [ ] Firmware development in progress

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

## 📜 License

Licensed under the [MIT License](../LICENSE)

---

## ⭐ Learning Goals

✅ Demonstrate embedded systems proficiency  
✅ Showcase multilayer PCB & Altium experience  
✅ Practice robust power management design  
✅ Build reliable firmware architectures  
✅ Apply real-world spacecraft subsystem integration 

---

## 🎯 Project Purpose

An academic and portfolio project to:

- Explore and apply **embedded hardware design** techniques  
- Implement **low‑power and fault‑tolerant architectures**  
- Design **custom PCBs** using **Altium Designer**  
- Interface subsystems via **STM32L496** and **SPI sensors**  
- Demonstrate engineering workflows for CubeSat systems  

This CubeSat project showcases my embedded systems skills through a complete 3-board satellite stack (OBC, EPS, Battery) and a custom Sun Sensor. It focuses on PCB design (Altium) and low-level firmware development using STM32 MCUs, highlighting real-world satellite subsystem integration for learning and demonstration purposes.