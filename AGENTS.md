# AGENTS GUIDE (ROOT SCOPE)

1. Purpose: concise rules for agents working in this repo.
2. Scope: applies to all files under repo root unless overridden by nested AGENTS.md (none exist now).
3. No Cursor rules found (.cursor/rules/, .cursorrules missing).
4. No Copilot instructions found (.github/copilot-instructions.md missing).
5. Repo type: C++17 SFML 3.0.0 app (macOS focus).
6. Primary entry: `src/main.cpp` with event loop and SFML window sample.
7. Build system: CMake (root `CMakeLists.txt`).
8. Binary target: executable `Paint` (macOS bundle configured when APPLE).
9. Dependencies: SFML 3 components Graphics, Window, System (find_package required).
10. Compiler expectation: clang++ on macOS ARM64 (from project brief).
11. Include path: `include/` added via target_include_directories.
12. Source path: `src/`.
13. Memory bank docs live in `memory-bank/` (project brief, system patterns, tech context, product context).
14. `prd.md` now captures MVP with toolbar (brush/eraser/clear/save) and palette.
15. README is minimal; rely on this guide for operations.
16. No tests or test directories currently present.
17. No formatting config files (.clang-format, .editorconfig, .clang-tidy) found.
18. No CI configs detected.
19. No package managers beyond CMake/SFML.
20. Default language standard: C++17 (CMAKE_CXX_STANDARD 17, required ON).
21. SFML 3 specific notes: `sf::VideoMode` uses `sf::Vector2u` brace-init; event polling returns `std::optional<sf::Event>`; event type checks via `is<sf::Event::Closed>()` pattern.
22. Build dir convention: `build/` (already present from prior configure).
23. Build configure (Debug example): `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`.
24. Build compile: `cmake --build build --config Debug` (or omit --config for single-config generators like Unix Makefiles).
25. Reconfigure after dep or toolchain changes; delete `build/` if cache stale.
26. Run app (macOS bundle): `./build/Paint.app/Contents/MacOS/Paint`.
27. Run app (non-bundle generator): `./build/Paint` if produced.
28. Clean build: `cmake --build build --target clean`.
29. Rebuild from scratch: remove `build/` then rerun configure + build.
30. Install step: not configured; do not assume `cmake --install` works.
31. Tests: none; if adding, prefer CTest integration; document new commands here.
32. Single-test guidance (future): `ctest -N` to list, `ctest -R <name>` to run filtered.
33. Linting: none configured; if adding, prefer clang-tidy via CMake target; document flags.
34. Formatting: absent; if introducing clang-format, confirm style with maintainers before enforcing.
35. Dependency management: rely on system SFML (Homebrew on macOS). Avoid vendoring unless necessary.
36. Platform: macOS ARM64 prioritized; ensure SFML libs match architecture.
37. Binary output currently in `build/Paint.app` (bundle) and supporting cmake files.
38. Do not commit build artifacts.
39. Git hooks: none custom; standard samples only.
40. Avoid adding new top-level tools without approval (npm, pip, etc.).
41. Preferred build generator: default CMake generator (likely Unix Makefiles on macOS CLI). Ninja acceptable if available but document.
42. C++ style: follow existing sample; keep includes minimal and ordered.
43. Include order: standard/library includes after third-party? Current file uses third-party then standard; aim for: standard C++ headers, then third-party (SFML), then project headers.
44. No `using namespace` at global scope.
45. Prefer `auto` only when type is obvious from context; otherwise spell types for clarity.
46. Prefer `const` correctness: use `const` references when not modifying.
47. Use `constexpr` for compile-time constants where reasonable.
48. Naming: Types/structs/classes PascalCase; functions/methods camelCase; variables camelCase; constants `kPascalCase` or `kCamelCase` (choose consistently per file); enums PascalCase with enumerators PascalCase.
49. Files: headers `.hpp` or `.h` (not present yet); sources `.cpp`.
50. Header guards: prefer `#pragma once` for new headers.
51. Error handling: avoid empty catch blocks; handle expected failures with early returns or conditionals; prefer `std::optional`/`std::expected` patterns when available (C++17 optional already used).
52. Resource management: RAII; avoid raw new/delete; prefer stack objects or smart pointers.
53. Threading: none present; if added, prefer `std::thread`/`std::jthread` (C++17 has `std::thread` only).
54. Logging: none; use `std::cerr` for temporary diagnostics; remove noisy debug prints before merging.
55. Assertions: use `assert` for invariants in debug builds; avoid throwing in hot paths unless needed.
56. SFML window loop: keep event polling in while-loop, handle close event, clear/draw/display each frame.
57. Coordinates: use brace-init for vectors (e.g., `{800, 600}`) per sample.
58. UI layout: toolbar and palette are right-docked, positioned using current view top-left/size; keep padding constants from `config.hpp`.
59. Buttons: use rectangle shapes with simple icon rectangles; highlight on hover/active; actions = Brush/Eraser/Clear/Save.
60. Palette: vertical swatches under toolbar; clicks set brush color and exit drawing mode.
61. Shapes: set origin/position with float literals and brace-init.
59. Time/clock: if added, use `sf::Clock` from SFML 3 or std chrono; avoid manual sleep loops.
60. Input handling: check event type with `event->is<...>()`; avoid old 2.x style switch unless verified for SFML 3.
61. Build flags: default from CMake; add warnings via `target_compile_options(Paint PRIVATE -Wall -Wextra -Wpedantic)` if needed (confirm with maintainer before enforcing).
62. Link order handled by CMake; keep target_link_libraries entries minimal.
63. New dependencies: prefer find_package over vendored sources; update docs here when adding.
64. File organization: keep sources in `src/`, headers in `include/`; avoid cluttering root.
65. Tests location (future): `tests/` or `test/` with CTest discovery; mirror structure of sources.
66. Fixtures/data: store under `tests/data` if needed.
67. Build artifacts: keep within `build/`; do not check in generated files.
68. Binary name collisions: avoid creating additional executables without updating guide.
69. Tooling discovery: CMake uses `find_package(SFML 3.0.0 ... REQUIRED)`; ensure SFML config files are on CMAKE_PREFIX_PATH (Homebrew sets `/opt/homebrew` on macOS ARM).
70. Environment variables: typically none; if SFML not found, set `SFML_DIR` to SFML config path.
71. macOS bundle properties set in CMake (GUI identifier `com.kilo.paint`, bundle name `Paint`).
72. If adding Info.plist keys, modify CMake properties accordingly.
73. Documentation: update this AGENTS.md when adding tooling, deps, or style rules.
74. Memory bank: reference `memory-bank/` files for context before major changes; keep them updated if scope shifts.
75. `plan.md` exists—review for work planning if relevant.
76. Keep code minimal and focused; avoid speculative abstractions.
77. Performance: not critical for current scope; prioritize readability and correctness.
78. Thread safety: SFML window must be manipulated on main thread.
79. Event loop exit: honor `sf::Event::Closed` to close window.
80. Optional usage: event polling returns `std::optional`; check truthiness before deref.
81. C++17 features allowed: structured bindings, `if constexpr`, `std::optional`, `std::variant` (if needed), `std::filesystem` (if available via stdlib version).
82. Avoid deprecated SFML 2.x APIs; follow SFML 3 docs.
83. Coordinate types: prefer `sf::Vector2f`/`sf::Vector2u` as appropriate; do not mix raw ints/floats without intent.
84. Color: use `sf::Color` predefined or RGBA constructors.
85. Geometry: set origin to center when rotating/scaling shapes to avoid drift.
86. Rendering order: clear -> draw -> display; do not draw after display within same frame.
87. Timing: if adding frame timing, use `sf::Clock` to compute delta.
88. Input devices: handle via event types (Closed, Resized, KeyPressed, MouseButtonPressed, MouseMoved). Confirm SFML 3 enums.
89. Resource loading: if adding textures/fonts, load once and reuse; check return values.
90. File paths: prefer relative to working dir; for bundle, consider resource path handling separately if implemented.
91. Error messages: concise, actionable; avoid crashing without message when failures occur.
92. Third-party additions: document license implications; avoid embedding binaries.
93. Testing philosophy (when added): start with unit tests near logic; use CTest; keep deterministic.
94. Determinism: avoid randomness without seeding; if randomness used, allow seed override.
95. Build caching: safe to reuse `build/` between edits; rerun configure if CMakeLists changes.
96. IDE integration: CMake project; CLion/VSCode CMake Tools usable; keep compile_commands.json if generated but avoid committing.
97. Warnings-as-errors: not enforced; do not enable globally without discussion.
98. Code comments: keep concise; document non-obvious behavior.
99. APIs: expose minimal surface; keep functions static/internal where possible.
100. Namespaces: consider wrapping future code under project namespace (e.g., `paint`); avoid global functions for shared utilities.
101. Constexpr data: use for immutable configuration where practical.
102. Input validation: check sizes/ranges when reading external data.
103. Memory: prefer stack allocation; avoid owning raw pointers.
104. Move semantics: implement/enable when storing movable types; defaulted special members fine when appropriate.
105. Templates: avoid over-templating; keep simple.
106. Headers: avoid including heavy headers in other headers; forward-declare when possible.
107. Cycles: keep dependencies acyclic; consider splitting utilities.
108. Build speed: keep translation units small; only include necessary headers.
109. Static analysis: if running clang-tidy manually, keep presets lean; do not add config without consensus.
110. Formatting fallback: emulate LLVM style (4 spaces indent, brace on same line for functions) until formal config exists.
111. Line length: aim <= 100 chars; wrap for readability.
112. Trailing whitespace: avoid.
113. New files: add brief header comment describing purpose; omit license headers unless requested.
114. Git hygiene: do not commit build outputs or OS files.
115. Branching: follow team conventions; none specified.
116. Commits: only when explicitly requested by user; include rationale if made.
117. Pull requests: if created, summarize build/test evidence; link issues.
118. Secrets: none expected; do not store credentials.
119. Network: project local; no network calls needed.
120. Tool versions: CMake >=3.20; SFML 3.0.0; C++17.
121. Apple frameworks: SFML handles; no manual linkage required.
122. Packaging: not configured; if adding, document steps.
123. Hotkeys: not applicable.
124. Localization: not considered.
125. Accessibility: not applicable for now.
126. Assets: none present; if adding, store under `assets/` and reference in CMake if needed.
127. Continuous integration: absent; if adding CI, reflect build/test commands here.
128. Code review: favor small diffs; explain SFML-specific choices.
129. Error propagation: return early with clear message; avoid silent failures.
130. Optional/variant: prefer pattern matching with `std::visit` when needed; avoid unchecked get.
131. Pointers to SFML resources: SFML manages resource lifetimes; keep objects alive longer than window draws.
132. Threaded rendering: avoid; SFML expects single-threaded rendering.
133. Keyboard/mouse state: use event-driven handling; avoid tight polling.
134. Frame pacing: if adding, use `sf::sleep` or clocks; avoid busy-wait.
135. Build artifacts in repo currently from prior builds; consider cleaning before distribution.
136. Documentation updates: modify this file when introducing new rules or tools.
137. When uncertain: follow SFML 3 docs and standard C++17 best practices; avoid SFML 2.x references.
138. Debugging: use lldb with `--` for args; can run `lldb ./build/Paint.app/Contents/MacOS/Paint`.
139. Profiling: not set up; use Instruments if needed; avoid adding profiler deps.
140. Sanitizers: can add via `-fsanitize=address` etc. through CMake options locally; do not commit those flags unless approved.
141. Cross-platform: primary target macOS; if adding Windows/Linux support, guard platform-specific code.
142. Binary names: keep `Paint` unless strong reason to change.
143. Resource paths in bundle: consider using `NSBundle` queries if later needed; currently none.
144. Licensing: none stated; do not add licenses without approval.
145. Storage: no persistence; if adding, separate IO from rendering loop.
146. Input focus: handle window focus events if later needed; not present now.
147. Window resizing: if handling `sf::Event::Resized`, adjust view appropriately.
148. Coordinate units: consistent floats for drawing; avoid mixing int/floats unchecked.
149. Agent reminder: keep responses concise, avoid speculative changes, and align with above rules.
150. Update line count target: file intentionally ~150 lines for clarity.
