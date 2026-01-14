# Project Plan: Paint (SFML 3, C++17)

## Objectives
- Maintain a minimal SFML 3 windowed app as a Paint foundation.
- Ensure macOS ARM64 build reliability via CMake.
- Prepare for future drawing features (brushes, colors, canvas state).

## Current State
- SFML 3 window renders and supports brush/eraser drawing with palette and toolbar.
- Build system uses CMake; dependencies: SFML 3 Graphics, Window, System.
- No tests, no formatting config.

## Assumptions
- Target platform: macOS ARM64 with Homebrew-provided SFML 3.0.0.
- Compiler: clang++; standard: C++17 (per `CMakeLists.txt`).
- No additional assets or persistence yet.

## Build & Run
- Configure (Debug example): `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build --config Debug`
- Run (bundle): `./build/Paint.app/Contents/MacOS/Paint`
- Clean: `cmake --build build --target clean`
- Rebuild from scratch: delete `build/`, reconfigure, rebuild.

## Near-Term Tasks
1) Refine toolbar to MS Paint-like layout (brush, eraser, clear, save) with icons.
2) Dock palette to right below toolbar and ensure view-aware positioning.
3) Maintain brush/eraser parity (radius, alignment) and save/clear actions.
4) Document updated UX in `prd.md` and operational rules in `AGENTS.md`.
5) Establish testing approach (likely CTest) once logic grows; start with unit tests for non-graphics utilities.

## Engineering Guidelines (summary)
- Follow SFML 3 patterns: `window.pollEvent()` returns `std::optional`; use `event->is<sf::Event::Closed>()` etc.
- Include order: standard, third-party (SFML), then project headers.
- No global `using namespace`; prefer explicit types; use `auto` only when obvious.
- Prefer `const` correctness and RAII; avoid raw new/delete.
- Coordinate brace-init (e.g., `{800, 600}`) and float literals for positions/sizes.
- Rendering order per frame: clear -> draw -> display.

## Risks / Unknowns
- `prd.md` lacks requirements; clarify feature goals before expanding UI.
- No CI; manual builds only. Consider adding CI once scope grows.
- No formatting config; adopt LLVM-like style if adding clang-format later.

## Next Steps
- Fill `prd.md` with MVP requirements and user flows.
- Implement basic brush drawing and color selection stubs.
- Add lightweight utility tests once non-graphics logic appears.
- Update `AGENTS.md` if tooling/dependencies change.
