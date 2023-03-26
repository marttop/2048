# 2048

## Description

This is a simple implementation of the popular 2048 game in C++ using the Raylib game library. The game is played on a 4x4 grid and the objective is to combine tiles with the same number to reach the tile with the value of 2048.

## Build
### Linux - Debian
- Install clang:  
  - ```wget https://apt.llvm.org/llvm.sh```  
  - ```chmod +x llvm.sh```  
  - ```sudo ./llvm.sh <version number>```  
- Run ```sudo apt install g++``` (for GNU compiler) or ```sudo apt install clang``` (for clang compiler)
- [Install raylib on linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
- Run ```sudo apt install cmake```
- Run ```sudo apt install ninja-build```

### Macos

- Clang should come with Xcode
- Run ```brew install raylib```
- Run ```brew install ninja```
- Run ```brew install cmake```

Clone the submodules
```bash
git submodule update --init --recursive
```

Build the dependencies
```bash
./build_submodules.sh
```

Build the project
```
mkdir build
cd build
cmake -G "Ninja" ..
cmake --build . --target all
```

## Troubleshooting

If you ever run to something similar during execution

```bash
dyld[23707]: Library not loaded: raygui.dynlib
  Referenced from: <8487F789-1CFC-3D75-B1DD-B2CC8576963F> /Users/martonszuts/Code/C++/RayLib/2048/build/Gpt-test
  Reason: tried: 'raygui.dynlib' (no such file), '/System/Volumes/Preboot/Cryptexes/OSraygui.dynlib' (no such file), 'raygui.dynlib' (no such file), '/usr/local/lib/raygui.dynlib' (no such file), '/usr/lib/raygui.dynlib' (no such file, not in dyld cache), '/Users/martonszuts/Code/C++/RayLib/2048/raygui.dynlib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/martonszuts/Code/C++/RayLib/2048/raygui.dynlib' (no such file), '/Users/martonszuts/Code/C++/RayLib/2048/raygui.dynlib' (no such file), '/usr/local/lib/raygui.dynlib' (no such file), '/usr/lib/raygui.dynlib' (no such file, not in dyld cache)
[1]    23707 abort
```

Run this command **after replacing the placeholder with yout path**

```bash
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:YOUR/PATH/TO/THE/REPOSITORY/2048/submodules/raygui
```

## Submodules

- [nlohmann/json - release/v3.11.2](https://github.com/nlohmann/json/tree/v3.11.2)
- [raysan5/raygui - 3.2](https://github.com/raysan5/raygui/tree/3.2)