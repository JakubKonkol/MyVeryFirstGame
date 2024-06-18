# My Very First Game
Game created with C++ and SDL

## Compiling
### MacOS & Linux
- Install SDL2, SDL2_image, SDL2_ttf (Make sure Homebrew is installed if using macOS)
```bash
brew install SDL2 SDL2_image SDL2_ttf 
```
- Using make command will compile and run game
```bash
 make
```
### Windows
1. Install Mingw64 from  [here](https://www.mingw-w64.org/)
2. Install make for windows
```bash
winget install ezwinports.make
```
3. Download and extract SDL, SDL_image, SDL2_ttf 
4. In Makefile specify path to sdl
5. Using make command will compile and run game
```bash
 make
```