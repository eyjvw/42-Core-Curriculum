# cub3D

*This project has been created as part of the 42 curriculum by hkeromne and sbonneau.*

## Description

**cub3D** is a graphics programming project from the 42 cursus inspired by the classic game **Wolfenstein 3D**.  
The goal of the project is to create a **real-time 3D representation of a maze** using a **raycasting** technique, entirely written in C and using the **MiniLibX** graphical library.

Through this project, students learn the fundamentals of:
- Computer graphics
- Raycasting and 3D projection
- Event handling (keyboard and window events)
- Parsing configuration files
- Managing performance and memory in C

The program reads a `.cub` configuration file describing textures, colors, and a map layout, then renders a first-person view that the player can navigate.

---

## Features

- Real-time raycasting engine
- Textured walls with North, South, East, and West orientations
- Player movement (forward, backward, strafe, rotate)
- Collision detection with walls
- Configurable map via `.cub` file
- Floor and ceiling color rendering
- Proper window and resource management

---

## Instructions

### Requirements

- **Operating System:** Linux or macOS
- **Compiler:** `gcc`
- **Libraries:**
  - MiniLibX (provided by 42)
  - Standard C libraries (`math`, `stdlib`, `unistd`, etc.)

### Build

```bash
make
```

This generates the `cub3D` executable.

### Usage

```bash
./cub3D maps/example.cub
```

### Makefile rules

- `make` / `make all`: build the binary
- `make clean`: remove object files
- `make fclean`: remove binary and artifacts
- `make re`: full rebuild

### Controls

- `W` / `S`: move forward / backward
- `A` / `D`: strafe left / right
- `<-` / `->`: rotate camera left / right
- `ESC`: exit the program
- Window close button: clean exit

## Map Format (`.cub`)

A `.cub` file contains:

- Texture paths for each wall direction (`NO`, `SO`, `WE`, `EA`)
- Floor (`F`) and ceiling (`C`) colors, as `R,G,B`
- A map composed of:
  - `1` for walls
  - `0` for empty spaces
  - `N`, `S`, `E`, `W` for the player starting position and orientation

Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

## Technical Choices

- Raycasting algorithm based on DDA (Digital Differential Analysis)
- Single-threaded rendering loop for simplicity and clarity
- Strict error handling for invalid maps and configuration files
- Manual memory management to comply with 42 standards
- MiniLibX used exclusively for window creation and pixel rendering

## Notes

This project strictly follows the constraints and norms of the 42 cursus, including:

- No forbidden functions
- No memory leaks
- Norm-compliant C code

## Resources

### Raycasting & Graphics

- Lode Vandevenne — Raycasting Tutorial: https://lodev.org/cgtutor/raycasting.html
- Wikipedia — Ray casting: https://en.wikipedia.org/wiki/Ray_casting
- Wolfenstein 3D source code (historical reference)

### MiniLibX

- 42 Docs — MiniLibX documentation
- Community tutorials and examples from 42 students

### C Programming

- The C Programming Language — Kernighan & Ritchie
- Linux man pages (`man 3 mlx`, `man malloc`, etc.)

## AI Usage

AI tools were used only as a support resource, not as a code generator for the final project:

- To clarify theoretical concepts such as raycasting mathematics and DDA logic
- To review explanations of MiniLibX behavior and common pitfalls
- To improve documentation quality, including README structure and wording

All implementation decisions, algorithms, and final code were written and validated by the
project authors in compliance with 42 rules.
