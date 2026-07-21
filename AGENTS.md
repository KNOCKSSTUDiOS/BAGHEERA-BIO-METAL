# AGENTS.md — Guide for AI agents working in this repository

## Build

```bash
cmake -B build && cmake --build build
```

## Run

```bash
./build/bagheera_engine
```

The binary loads `config/bagheera.cfg` on boot if present (falls back to hardware defaults if missing).

## Project Structure

```
/
├── CMakeLists.txt          Single root build file (C++17, no globbing)
├── .gitignore
├── AGENTS.md               This file
├── README.md
├── config/
│   └── bagheera.cfg        Engine config (key:value pairs)
├── src/                    C++ engine sources
│   ├── main.cpp            Engine lifecycle entry point
│   ├── app_core.cpp        Audio DSP (biquad filter) + engine boot/diagnostics
│   ├── config_parser.cpp   Config file parser
│   ├── system_io.cpp       Local storage + memory buffer allocation
│   ├── platform_bridge.cpp Platform event/render-command bridge
│   └── system_diag.cpp     Frame timing + memory diagnostics
├── include/                C++ headers
│   ├── app_core.hpp
│   ├── config_parser.hpp
│   ├── platform_bridge.hpp
│   └── system_diag.hpp
├── index.html              HTML5/Three.js demo layer (standalone)
├── render_bday.html        Birthday render variant (standalone)
├── ultra_render.html       Ultra render variant (standalone)
└── console_js              JS UI interface context (standalone)
```

## Conventions

- **C++ standard:** C++17
- **Build system:** Single root `CMakeLists.txt`; sources listed explicitly (no globbing)
- **Headers:** All public headers go in `include/`
- **Sources:** All `.cpp` files go in `src/`
- **Dependencies:** Standard library only — no external libraries required
- **Config:** `config/bagheera.cfg` uses `key: value` lines, `#` for comments
- **Commits:** Conventional commit messages

## Architecture

The C++ core engine (`src/` + `include/`) is a standalone native binary that exercises a biquad low-shelf audio filter, microsecond frame timing, real memory allocation, and a platform event bridge. It is dependency-free and builds on any standard C++17 toolchain.

The HTML5/WebGL demo layer (root `.html` files + `console_js`) is a separate, standalone front-end that runs in any browser. It uses Three.js loaded from CDN and does not depend on the C++ build. The two layers are independent.
