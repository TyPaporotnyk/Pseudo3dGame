# Pseudo3DGame

Pseudo 3d implementation by c++ and sfml

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](http://choosealicense.com/licenses/mit/)
![Commits](https://img.shields.io/github/last-commit/TyPaporotnyk/Pseudo3dGame)
![Version](https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B)
![Repo size](https://img.shields.io/github/repo-size/TyPaporotnyk/Pseudo3dGame)


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
cmake -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release
cmake --build cmake-build-release --target release
```

# Control
| Action               | Control         |
| ---------------------|-----------------|
| Move                 | WASD keys       |
| Rotation             | Mouse movement  |
| Exit                 | Q key           |
| Pause                | Esc             |
