# Star Breaker

## Description

Brick/Block breaker project, made in raylib.

## Build

Clone the submodules
```bash
git submodule update --init --recursive
```

Build the dependencies
```bash
./build_submodules.sh
```

## Troubleshooting

If you ever run to something similar during execution

```bash
dyld[23707]: Library not loaded: raygui.dynlib
  Referenced from: <8487F789-1CFC-3D75-B1DD-B2CC8576963F> /Users/martonszuts/Code/C++/RayLib/star-breaker/build/Gpt-test
  Reason: tried: 'raygui.dynlib' (no such file), '/System/Volumes/Preboot/Cryptexes/OSraygui.dynlib' (no such file), 'raygui.dynlib' (no such file), '/usr/local/lib/raygui.dynlib' (no such file), '/usr/lib/raygui.dynlib' (no such file, not in dyld cache), '/Users/martonszuts/Code/C++/RayLib/star-breaker/raygui.dynlib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/martonszuts/Code/C++/RayLib/star-breaker/raygui.dynlib' (no such file), '/Users/martonszuts/Code/C++/RayLib/star-breaker/raygui.dynlib' (no such file), '/usr/local/lib/raygui.dynlib' (no such file), '/usr/lib/raygui.dynlib' (no such file, not in dyld cache)
[1]    23707 abort
```

Run this command **after replacing the placeholder with yout path**

```bash
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:YOUR/PATH/TO/THE/REPOSITORY/star-breaker/submodules/raygui
```

## Submodules

- [nlohmann/json - release/v3.11.2](https://github.com/nlohmann/json/tree/v3.11.2)
- [raysan5/raygui - 3.2](https://github.com/raysan5/raygui/tree/3.2)