# Modular Pong: Custom C Game Engine

![Language: C](https://img.shields.io/badge/Language-C11-blue.svg)
![Graphics: Raylib](https://img.shields.io/badge/Graphics-Raylib_4.0+-red.svg)
![Build: CMake](https://img.shields.io/badge/Build-CMake-green.svg)

A modern recreation of the classic arcade game *Pong*, built from scratch using a custom 2D game engine written entirely in standard C.

Rather than relying on high-level commercial engines (like Unity or Godot), this project serves as a practical exploration of low-level software architecture, memory management, and real-time application loops.

##  Core Technical Features

* **Custom Game Loop:** Hard-coded continuous input/update/render loop locked at a stable 60 FPS.
* **Finite State Machine (FSM):** Seamlessly routes logic and memory processing between Interactive Menus, Active Gameplay, Pause States, and Game Over sequences.
* **Algorithmic Physics:** Custom circle-to-rectangle boundary checking and an "edge-slice" variable velocity system that calculates bounce angles based on impact distance from the paddle's center.
* **Data Encapsulation:** Game entities (ball, paddles, scores) are managed via C `structs` and manipulated strictly through memory pointers to prevent overhead.
* **Reactive AI:** A mathematical tracking algorithm that calculates dynamic Y-axis intercepts for the CPU opponent, complete with scalable difficulty tiers.
* **Dynamic Audio:** Hardware-accelerated `.wav` and `.mp3` audio streaming using Raylib, with strict RAM management to prevent memory leaks.

##  Prerequisites

To compile and run this project locally, you will need:
* A C Compiler (GCC or Clang)
* [CMake](https://cmake.org/) (Version 3.15 or higher)
* [Raylib](https://www.raylib.com/) installed on your system (or fetched via CMake)

## Building and Running

This project uses CMake to handle the build process and link the Raylib graphics library.

**Using Terminal (macOS / Linux / Windows):**
1. Clone the repository:
   ```bash
   git clone [https://github.com/YourUsername/ModularPong.git](https://github.com/YourUsername/ModularPong.git)
   cd ModularPong

2. Create a build directory and run CMake:
    ````
    mkdir build
    cd build
    cmake ..
    make
3. Run the executable:
    ````
    ./PongBall
##  Controls

    Player 1 (Left Paddle): W (Up) / S (Down)

    Player 2 (Right Paddle): UP Arrow / DOWN Arrow

    Pause Game: P

    Restart (Game Over Screen): SPACEBAR

## Architecture Overview
* The codebase strictly adheres to modular design principles to separate logic from rendering:

* **main.c** - Entry point, window initialization, and the primary FSM Game Loop.

* **pong.h** - Data structures (Structs), constants, and function prototypes.

* **pong.c** - Physics algorithms, collision mathematics, and state mutation logic.

## What I Learned
Building this engine solidified my understanding of how software communicates with hardware. Resolving linker errors, mitigating **"tunneling"** in the collision physics, and **managing pointer memory addresses** provided invaluable, hands-on experience that high-level abstractions often hide.

Created by **Nipun Deept** - 1st Year Computer Science Engineering
