# Pseudo3DGame

| 90 rays                        | 400 rays                        |
| -------------------------------|---------------------------------|
| <img src="docs/90rays.png"/>  |  <img src="docs/400rays.png"/>  |

# Texturing

<img src="docs/texturing.png" width="auto"/>

# Requirements
* C++ 20
* CMake 3.20
* SFML 2.5

# Building & Running
```
cmake -B cmake-build -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build
cmake --build cmake-build --target release
```

# Control
| Action               | Control         |
| ---------------------|-----------------|
| Move                 | WASD keys       |
| Rotation             | Mouse movement  |
| Exit                 | Q key           |
| Show or hide map     | M key           |
