# 🐆 BAGHEERA-BIO-METAL

```text
       _   _   _   _   _   _   _   _   _   _   _   _   _   _   _ 
      / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
     ( K ( N ( O ( C ( K ( S ( S ( T ( U ( D ( i ( O ( S ) ) ) ) )
      \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ 
​"A pitch-black jungle. Complete silence. A stealth black panther stalks out of the shadows, lunging directly at the camera. The screen shatters into fluid, hyper-reflective liquid metal droplets that merge to form KNOCKSSTUDiOS, while bioluminescent June bugs scatter across the dark interface."
​🌌 The Vision
​BAGHEERA-BIO-METAL is a high-performance, hybrid cross-platform application engine designed for borderless tablet displays. Combining raw C++ computational horsepower with an ultra-fluid WebGL/HTML rendering pipeline, it creates immersive, photorealistic, stealth-themed visual user interfaces.
​Stealth Aesthetics: Deep obsidian black, dark jungle tones, and lethal red accents.
​Dynamic UI Fluidity: Real-time liquid mercury simulations shifting over an embedded alpha-channel media layer.
​Instanced Particle Systems: Real-time velocity tracking for interactive bioluminescent bug swarms that react dynamically to screen boundaries and impact events. 🧠 C++ CORE ENGINE             ⚡ INTERACTIVE UI LAYER
┌────────────────────────┐     ┌────────────────────────┐
│  • Microsecond Timers  │ ──> │  • Three.js WebGL      │
│  • Memory Management   │     │  • Shaders & Particles │
│  • System Diagnostics  │     │  • Liquid Metal Engine │
└────────────────────────┘     └────────────────────────┘
            │                              │
            ▼                              ▼
 📊 SQL STORAGE LAYER           🎛️ XML CONFIG CORE
┌────────────────────────┐     ┌────────────────────────┐
│  • Telemetry Logs      │     │  • Layout Rules        │
│  • Session State Data  │     │  • Particle Densities  │
└────────────────────────┘     └────────────────────────┘
1. 🧠 Core Engine (C++ / aarch64 Native)
​Handles low-level hardware link diagnostics, microsecond execution sweeps (SystemDiagnostics), and heap-allocated tracking arrays to ensure zero-latency frame performance on target devices.
​2. ⚡ Presentation Layer (HTML5 / CSS3 / Three.js WebGL)
​Pushes pure GPU-accelerated graphics directly to borderless screens. Features a responsive, customized liquid-metal text rendering framework and an organic vector-driven scattering matrix for environment particles.
​3. 🎛️ Configuration Layer (XML)
​System configurations, environment bounds, particle limits (e.g., bugCount = 200), and material reflectivity settings are mapped dynamically using clean schema architectures.
​4. 📊 Storage & Analytics Layer (SQL)
​Structured telemetry tracking datasets logging frame rates, system memory loads, and localized interface execution data across user interactions.
​## Project Structure

```
BAGHEERA-BIO-METAL/
├── CMakeLists.txt            Single root build file (C++17, explicit source list)
├── .gitignore
├── AGENTS.md                 Guide for AI agents working this repo
├── README.md
├── config/
│   └── bagheera.cfg          Engine config (key:value pairs)
├── src/                      C++ engine sources
│   ├── main.cpp              Engine lifecycle entry point
│   ├── app_core.cpp          Audio DSP (biquad filter) + engine boot/diagnostics
│   ├── config_parser.cpp      Config file parser
│   ├── system_io.cpp         Local storage + memory buffer allocation
│   ├── platform_bridge.cpp   Platform event/render-command bridge
│   └── system_diag.cpp       Frame timing + memory diagnostics
├── include/                  C++ headers
│   ├── app_core.hpp
│   ├── config_parser.hpp
│   ├── platform_bridge.hpp
│   └── system_diag.hpp
├── index.html                HTML5 / Three.js demo (standalone)
├── render_bday.html          Birthday render variant (standalone)
├── ultra_render.html         Ultra render variant (standalone)
└── console_js                JS UI interface context (standalone)
```

## Build & Run

The C++ core engine builds with CMake and a C++17 compiler. No external dependencies are required.

```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run
./build/bagheera_engine
```

The binary loads `config/bagheera.cfg` on boot if present. If the file is missing, it falls back to compiled-in hardware defaults.

### Example output

```
=== KNOCKSSTUDiOS // NATIVE APPLICATION BUILD ===
[CONFIG] Configuration file parsed successfully (5 keys loaded) completely offline.
[SYSTEM I/O] Allocation completed: 10 MB pristine runtime memory cache bound (10485760 bytes).
[MAIN] Config -> bugCount=200 | reflectivity=0.85 | sample_rate=48000
[DIAGNOSTIC] Filter: low-shelf 30Hz @ +12dB | sample_rate=48000Hz
[DIAGNOSTIC] Measured output over 4096 samples -> peak=1.18943 | RMS=0.586213
[TELEMETRY] Average frame time over 5 frames: 291.2 microseconds.
[MEMORY] Buffer allocated: 10 MB | running total tracked: 10 MB (10485760 bytes).
=== BUILD LIFECYCLE COMPLETED CLEANLY ===
```

## Architecture

### C++ Core Engine

The native binary (`bagheera_engine`) is a dependency-free C++17 program that exercises the core systems the full VFX pipeline would rely on:

- **AppAudioProcessor** — Real biquad low-shelf filter with standard coefficient math. Processes audio buffers and reports measured RMS/peak levels. Used to validate the sub-bass diagnostic signal path.
- **KnocksAppEngine** — Engine lifecycle: boot, allocate real memory (10 MB pool), create local storage directory via `std::filesystem`, load config, run diagnostics, and clean shutdown.
- **SystemDiagnostics** — Microsecond frame timing with a rolling average over the last N frames, plus cumulative memory tracking.
- **PlatformBridge** — Attaches input callbacks, broadcasts engine state transitions, logs structured render commands, and dispatches input events to handlers.
- **ConfigParser** — Parses `key: value` config files with comment support. Used for particle counts, reflectivity, sample rate, and filter parameters.

### HTML5 / WebGL Demo Layer

The root-level `.html` files and `console_js` are a standalone front-end that runs in any modern browser. They use Three.js (loaded from CDN) for GPU-accelerated liquid-metal simulations, particle systems, and shader effects. This layer does not depend on the C++ build — the two are independent and can be developed separately.

| Layer | Tech | Purpose |
|---|---|---|
| C++ Core | C++17, CMake, std lib only | Audio DSP, memory, timing, platform bridge |
| Web Demo | HTML5, Three.js, WebGL | Liquid-metal VFX, particles, visual interface |
