# Langton's Ant

A C implementation of [Langton's Ant](https://en.wikipedia.org/wiki/Langton%27s_ant) — a simple cellular automaton that produces surprisingly complex, emergent behavior from just two rules.

![Langton's Ant Animation](examples/ant.gif)

## The rules

- On a **white** cell: turn 90° clockwise, flip the cell to black, move forward.
- On a **black** cell: turn 90° counter-clockwise, flip the cell to white, move forward.

Starting from a mostly-white grid, the ant initially moves chaotically for a few thousand steps, then settles into building a repeating diagonal "highway" pattern.

## Features

- Configurable grid size and step count
- Boundary handling: the ant bounces off the edges of the grid instead of running out of bounds
- Exports the grid as a `.ppm` image
- Can export snapshots at intervals to build an animation (see below)

## Building & running

Requires a C compiler (tested with GCC/Clang) and optionally CMake.

```bash
# with CMake
cmake -B cmake-build-debug
cmake --build cmake-build-debug
./cmake-build-debug/langtons_ant

# or directly with gcc
gcc main.c -o langtons_ant
./langtons_ant
```

Make sure a `frames/` directory exists in the project root before running, since that's where the snapshot images are written.

## Creating an animation

The program periodically saves the grid as `frames/frame_XXXX.ppm`. These can be combined into a video or GIF with [ffmpeg](https://ffmpeg.org/):

```bash
cd frames
ffmpeg -framerate 30 -i frame_%04d.ppm -vf "scale=800:800:flags=neighbor" -c:v libx264 -pix_fmt yuv420p ant.mp4
```

The `flags=neighbor` scaling keeps the pixels crisp instead of blurring them.

## What I practiced with this project

This was a learning project to get hands-on with core C concepts:

- Structs and enums (`Ant`, `Direction`)
- Pointers and pass-by-reference (`step(Ant *ant)`)
- 2D arrays and manual bounds checking
- File I/O (`fopen`/`fprintf`/`fclose`) and basic error handling
- Building a minimal image format (PPM) from scratch
