# CHIP-8-Emulator
 CHIP-8 emulator written in C++

## Dependencies
* SDL2 - https://www.libsdl.org/

## Compilation 
The program can be built with any C++ compiler. Here is an example using MSVC:
```
cl.exe -EHsc Source/*.cpp -I Headers/ -I SDL2/include/ -Fo:Build/ -Fe:Build/Chip-8-Emulator.exe /link /LIBPATH:SDL2/lib/x64/ SDL2main.lib SDL2.lib Shell32.lib -SUBSYSTEM:CONSOLE
``` 

## How to Run
```
 CHIP-8-Emulator.exe <path-to-rom> <instructions-per-second>
```

**Instructions per second** - How many instructions the CPU should fetch/execute each second. The ideal number for this varies between ROMs, but 500 - 1000 seems to be a good range.

## Keypad Layout
```
1 2 3 4
Q W E R
A S D F
Z X C V
```

## References
* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
* https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
* https://en.wikipedia.org/wiki/CHIP-8
