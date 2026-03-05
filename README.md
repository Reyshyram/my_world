# My World

A 3D isometric map editor

## Usage/Examples

```
$ ./my_world -h
Usage: ./my_world [-h|--help]

How to move the camera:
- Arrow keys to move the camera
- Q and D to rotate the camera
- Z and S to zoom in and out
- Shift or Ctrl to change movement speed

How to modify the world:
- Right click to select a block
- Click on a button to activate an effect
- More informations about the effects/shortcuts in the tooltips
```

## How to compile/run

Simply use make to compile the program:

```bash
make -j
```

And then run the resulting binary, in this case, `my_world`.
By default, the Makefile uses epiclang. To compile with something else, you can simply modify the value of CC like this:
```bash
make -j CC=gcc
```

## Running Tests

To execute the unit tests, use the tests_run rule, which will compile the tests and execute the resulting binary.

```bash
make -j tests_run
```

> [!WARNING]
> This program is leaved as is, without any warranty. Use at your own caution.
> Moreover, this is a school project. Epitech students, beware the -42.
