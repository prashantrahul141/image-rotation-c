# Image rotation in C.

Rotate images using [Sampling algorithm](https://www.sciencedirect.com/topics/computer-science/image-rotation)

### Building

This uses a simple Makefile, just run (with [make](https://www.gnu.org/software/make/) installed):

```sh
make
```

### Usage

```sh
Usage:
    main [rotation in degrees] [file path]
```

example:

```sh
./main 15 ./images/pixel_art.png
./main 52 ./images/arch.png # or any arbitary angle
./main 180 ./images/2x2.png
```

### Images

[./images/pixel_art.png](https://github.com/prashantrahul141/image-resizing-c/blob/main/images/pixel_art.png) - Scene from KatanaZero.
