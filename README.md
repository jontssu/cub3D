# Cub3D

Cub3D is a graphic game project inspired by the world-famous 90's game Wolfenstein 3D, which was the first FPS ever. The project is about creating a dynamic view inside a maze. The player can look around and navigate through the maze.

This project uses the concepts of ray-casting and was implemented in C language.

## Prerequisites

* A Unix-like operating system: macOS, Linux
* gcc
* make
* C Library
* MiniLibX

## Installing

Clone the repository and navigate into the directory:

```bash
git clone https://github.com/jontssu/cub3D.git
cd <repo>
```

## Compiling
Compiling the executable can be done with:
```bash
make
```
## Running
After compiling, you can run the program with:
```bash
./cub3d <name_of_map_file>.cub
```
## Keybindings
Arrows Left/Right: Look left/right.  
Key | action
--- | ---
`W` | Move forward.  
`A` | Move left.  
`S` | Move backward.  
`D` | Move right.  
`ESC` | Quit the program.
## Game Map Configuration
A game map file must be passed as a parameter to the program. This file should have the extension .cub.
## Map Characters:
Character | Representation
--- | ---
`0` | Empty space.  
`1` | Wall.  
`N, S, E, W` | Player’s start position and spawning orientation.  
## Example:
```bash
111111
100101
101001
1100N1
111111
```
## Texture and Color Settings:
You can specify the path to the wall texture files and the colors of the floor and ceiling.

Example:
```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
```
## Map Configuration Errors
If the map configuration file doesn't meet the requirements, the program will exit and return "Error\n" followed by an explicit error message.
