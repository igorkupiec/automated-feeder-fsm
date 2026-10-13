# Automated Cigarette Injector Machine (3D Printed & CNC-based)

A DIY, low-cost fully automated/semi-automated cigarette injector system built using 3D-printed custom parts, linear mechanics (NEMA 17, lead screw, linear rods), and a modified manual/electric injector unit mounted on a rigid wooden base.

![Project Status](https://img.shields.io/badge/status-in__development-yellow)
![License](https://img.shields.io/badge/license-MIT-blue)

---

## 📌 Project Overview

The main objective of this project is to automate the process of loading and injecting tobacco into cigarette tubes. The design leverages affordable desktop 3D printing, standard 3D printer hardware (NEMA 17 stepper motors, 8mm linear rods, lead screw), and an OSB wooden base for mounting and damping.

### Key Features
* **Modular Mechanics:** Custom 3D printed supports, corner brackets, and motor mounts designed in CAD.
* **Linear Motion:** Smooth slide carriage operating on 8mm steel linear guides ($8.3\text{ mm}$ clearance tolerances for bushing-free operation) driven by an M5 lead screw.
* **Vibration Damping:** Custom OSB base ($600 \times 300 \times 18\text{ mm}$) featuring corner brackets with anti-slip rubber/felt inserts to isolate motor chatter and vibration.
* **Dual Stepper Motor System:** Dedicated NEMA 17 motors for linear tube positioning and tobacco injector lever operation.

---

## 🛠️ Hardware & Components

### Mechanical Parts
* **Base:** OSB Wooden Board ($600 \times 300 \times 18\text{ mm}$)
* **Linear Rails:** $2\times$ 8mm smooth steel linear rods
* **Lead Screw:** M5 lead screw + brass nut
* **Injector Unit:** Compact manual/electric tobacco injector base
* **Fasteners:** M4 countersunk screws, wood screws, double-sided mounting tape, rubber/felt anti-slip pads

### Electronics & Actuators
* **Motors:** $2\times$ NEMA 17 Stepper Motors (Linear carriage axis + Lever axis)
* **Couplers:** $5\text{ mm} \times 5\text{ mm}$ / $5\text{ mm} \times 8\text{ mm}$ flexible shaft couplers
* **Controller:** Arduino / ESP32 with A4988 or TMC2209 drivers *(Planned)*
* **Sensors/Servos:** Optional Micro Servo (SG90) for passive/active tube ejection and limit switches for homing.

---

## 📁 3D Printed Parts (CAD Models)

All 3D parts are modeled for easy FDM printing without complex support structures (optimized printing orientations, teardrop horizontal holes, countersunk screw profiles):

1. **Corner Brackets (`corner_brackets.stl`):** Locks the main injector body to the OSB base with slots for anti-slip tape.
2. **Rod & Lead Screw Supports (`rod_supports_8.3mm.stl`):** Holds 8mm linear rods (8.3 mm printed holes for sliding fit) and M5 lead screw, featuring an arched cutout for tube clearance.
3. **Linear Carriage (`carriage_v1.stl`):** Rides on 8mm rods, holding the tube in place and advancing it smoothly onto the injector nozzle.
4. **NEMA 17 Motor Mounts (`nema17_mount_l.stl`):** Heavy-duty L-brackets for rigidly mounting motors to the OSB base.

---

## 🔧 Assembly & Alignment Notes

1. **Tolerances:** Linear rod holes are designed at $\varnothing 8.3\text{ mm}$ to compensate for FDM extrusion expansion, eliminating the need for press-fit brass bushings.
2. **Nozzle Alignment:** Mount the linear rod supports to the OSB board using standard cigarette tubes as physical calibration gauges to ensure zero-jam alignment with the metal injector nozzle.
3. **Vibration Isolation:** Apply 1–2 mm rubber pads under the corner brackets prior to screwing them onto the OSB board.

---

## 🚀 Roadmap

- [x] Design and print corner brackets & rod supports
- [x] Verify linear rod clearances ($\varnothing 8.3\text{ mm}$) and nozzle alignment
- [ ] CAD & 3D print NEMA 17 motor mounts (Linear drive & Lever mechanism)
- [ ] Mount motors, lead screw, and test mechanical carriage motion
- [ ] Design gravity-fed or servo-assisted cigarette tube magazine
- [ ] Electronics wiring, limit switch homing, and control software (C++/Arduino)

---

## 📜 License

This project is open-source under the [MIT License](LICENSE).