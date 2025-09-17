# Tetris in C

This is a simple implementation of the classic Tetris game in C using the SDL2 library.

## Features

*   Classic Tetris gameplay
*   All 7 tetromino shapes
*   Tetromino movement (left, right, down) and rotation
*   Line clearing and scoring
*   Increasing difficulty as the game progresses
*   Game over detection

## Dependencies

*   [SDL2](https://www.libsdl.org/): A cross-platform development library designed to provide low-level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.

## Getting Started

### Prerequisites

Make sure you have the SDL2 library installed on your system. You can install it using your favorite package manager. For example, on Debian-based systems, you can use the following command:

```bash
sudo apt-get install libsdl2-dev
```

### Building and Running

1.  Clone the repository:

    ```bash
    git clone https://github.com/raffscardoso/tetris-c.git
    ```

2.  Navigate to the project directory:

    ```bash
    cd tetris-c
    ```

3.  Build the project using the `make` command:

    ```bash
    make
    ```

4.  Run the game:

    ```bash
    ./tetris
    ```

## Controls

*   **Left Arrow:** Move the piece to the left
*   **Right Arrow:** Move the piece to the right
*   **Down Arrow:** Move the piece down faster
*   **Up Arrow:** Rotate the piece
*   **Z:** Drop the piece to the bottom
