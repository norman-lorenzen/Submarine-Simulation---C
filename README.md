Project: Autonomous Submarine Navigation & Depth Control Simulation
#### Video Demonstration: https://www.youtube.com/watch?v=_7mhlVtKtSY
#### Description:

This project is a highly efficient, deterministic, and hardware-near autonomous simulation of a submarine navigation and depth control system written in pure, 
native C. Developed as the Final Project for Harvard's CS50x, the architecture is entirely static and strictly `malloc`-free, ensuring absolute stability, 
dynamic memory safety, and zero memory leaks. It is optimized to run directly on embedded hardware structures such as the ARM Cortex-M4 microcontrollers used in 
advanced automation and marine engineering (e.g., TKMS or Tesla Automation).

### Core Features & Architecture

The system simulates live navigation telemetries by managing four core variables in a synchronized real-time execution loop: Speed (Knots), Depth (Meters), Course (Degrees), 
and Direction.

1. **Deterministic Depth Regulation (`calculate_depth`)**
   The depth algorithm utilizes an asymmetric dual-stage control loop combined with a precise tolerance deadband (hysteresis) of 0.15 meters. To mimic realistic hydrodynamics, 
   descending is accelerated (`+0.2m` per tick) while ascending is dampened (`-0.1m` per tick) to prevent dangerous vertical overshooting. The integrated hysteresis algorithm 
   prevents continuous oscillation around the target depth, locking the system stably onto the setpoint.

2. **Speed-Dampened Circular Navigation (`calculate_course`)**
   The course correction controller features an advanced "Brake-to-Turn" state machine and a shortest-path tracking loop across the $0^\circ / 360^\circ$ boundary. 
   Hard turns ($>30^\circ$ error) dynamically trigger a vessel deceleration protocol down to 4 knots to ensure safety against physical centrifugal forces. 
   Medium turns ($15^\circ$ to $30^\circ$) damp the system to 8 knots. The internal logic standardizes the floating-point angle to a strict $[0.0, 360.0[$ interval, avoiding 
   negative numeric errors and infinite looping during cross-zero turning.

### File Structure

* **`main.c`**: The primary executable file containing the core loop, the synchronized real-time state machines, and the live telemetries display engine.
* **`logik.c` / `navigation.h`**: The modular mathematical components hosting the isolated algorithmic blocks of `calculate_depth` and `calculate_course`.
* **`README.md`**: The technical architectural overview and deployment documentation for the Harvard review board.

### First-Principles Engineering Design

Unlike standard software projects that rely on bloated external libraries and heavy operating system wrappers, this system operates on pure mathematical equations 
and bit-level pointer manipulation logic. By encapsulating state configurations within static local variables, this codebase achieves absolute execution predictability 
in the microsecond range, making it highly secure against computational sabotages and system latencies.
