# so_long

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

`so_long` is a small 2D game project built with `minilibx`.
The player moves on a tile map, must collect all collectibles, then reach the exit.

The project validates map format and playability before launching, including:
- rectangular map
- closed walls
- valid characters (`0`, `1`, `C`, `E`, `P`)
- exactly one player start and one exit
- at least one collectible
- solvable path checks (flood fill)

## Controls

- `W` / `A` / `S` / `D`: move player
- `ESC`: close game
- window close button: clean exit

Each valid move is counted and printed.

## Build

### Requirements

- Linux
- `gcc`/`cc`
- X11 development packages
- `minilibx-linux` (already present or fetched with `make minilibx`)

### Build

```bash
make
```

### Makefile rules

- `make` / `make all` : build `so_long`
- `make clean` : remove object files + clean minilibx objects
- `make fclean` : remove binary + clean artifacts
- `make re` : full rebuild
- `make minilibx` : clone minilibx-linux repository

## Usage

```bash
./so_long maps/map.ber
```

Map must have `.ber` extension and valid content.

## Project Structure

- `main.c` : entry point
- `includes/` : headers, structs, prototypes, constants
- `utils/` : map parsing, validation, flood-fill, rendering, movement, cleanup
- `maps/` : test maps
- `textures/` : sprite assets
- `minilibx-linux/` : graphics library
- `mk/` : Makefile split (`variables.mk`, `colors.mk`, `rules.mk`)

## Core Flow

1. Parse CLI arguments
2. Read map file into memory
3. Validate map shape/content and run flood fill checks
4. Initialize MLX window and textures
5. Render map and handle input loop
6. Exit cleanly on win/close/error

## Resources

- [MiniLibX Linux](https://github.com/42paris/minilibx-linux)
- [X11 documentation](https://tronche.com/gui/x/xlib/)
- [42 Norminette](https://github.com/42School/norminette)

## AI Usage

AI assistance (GitHub Copilot) was used for:

1. Build system refactor (Makefile split in `mk/`)
2. Include path normalization (`-I includes/` + clean include directives)
3. README writing and project documentation

Core gameplay logic and project implementation were done manually.
