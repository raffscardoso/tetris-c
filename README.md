# Tetris in C

This is a complete implementation of the classic Tetris game written in C using the SDL2 library. It supports both native desktop compilation and WebAssembly (Wasm) builds for running in the browser.

## Features

*   **Classic Gameplay**: All 7 tetromino shapes with standard rotation and wall kicks.
*   **Game States**: Start Menu, Gameplay, High Scores, Pause Menu, and Game Over screen.
*   **Web Support**: Fully playable in the browser via WebAssembly (Emscripten).
*   **Cross-Platform**: Runs natively on Linux/macOS/Windows (wherever SDL2 runs) and on the web.

## Dependencies

### Native Build
*   **GCC** or another C compiler.
*   **SDL2**: `sudo apt-get install libsdl2-dev` (Debian/Ubuntu) or `brew install sdl2` (macOS).

### Web Build
*   **Emscripten (emsdk)**: Required to compile to WebAssembly.

## Controls

### Gameplay
*   **Arrow Left / Right**: Move piece horizontally.
*   **Arrow Up**: Rotate piece.
*   **Arrow Down**: Soft drop (faster fall).
*   **Z**: Hard drop (instant placement).
*   **Esc**: Pause Game / Open Menu.

### Menus
*   **Arrow Up / Down**: Navigate options.
*   **Enter**: Select option.

## Building and Running

### 1. Native Desktop Version

To build and run the game on your computer:

```bash
# Build the game
make

# Run the game
./tetris
```

### 2. Web Version (WebAssembly)

To build the game for the web, ensure you have `emcc` in your path (source your `emsdk_env.sh` first).

```bash
# Build for web (generates index.html, index.js, index.wasm)
make web
```

To play the web version, you must serve the files using a local web server (browsers often block local file access to Wasm):

```bash
# Start a simple Python server
python3 -m http.server 8000
```

Then open your browser and go to: [http://localhost:8000](http://localhost:8000)

## Project Structure

*   `main.c`: Entry point for the native desktop build.
*   `main_emscripten.c`: Entry point for the Web/Emscripten build (contains the main loop wrapper).
*   `game.c / game.h`: Core game logic (state machine, grid management, collision).
*   `sdl_handler.c / sdl_handler.h`: Rendering and window management.
*   `font.c / font.h`: Custom lightweight font rendering.
*   `shell_template.html`: HTML template for the web build.
*   `web_script.js`: Web-specific JavaScript logic.
*   `style.css`: Styles for the web interface.

## License

Free and open source.