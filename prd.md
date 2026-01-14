# Product Requirements: Paint (MVP)

## Vision
Deliver a lightweight Paint-style desktop app on macOS (SFML 3, C++17) focused on responsive freehand drawing with minimal UI.

## Target Platform
- macOS ARM64 (Apple Silicon)
- Windowed desktop app using SFML 3.0.0

## Personas
- **Casual doodler**: Wants a quick canvas to sketch ideas.
- **Developer/designer**: Needs a scratchpad for diagrams or annotations.

## Goals (MVP)
1. Launch reliably on macOS; open a resizable window with a sensible default size.
2. Support freehand drawing with a primary brush tool (mouse/touchpad).
3. Provide a visible toolbar with buttons for Brush, Eraser, Clear, and Save, styled after classic MS Paint.
4. Allow changing brush color via a docked palette; brush radius stays consistent between tools.
5. Maintain drawn strokes across frames (no flicker, no auto-clear) and enable save-to-PNG.

## Non-Goals (MVP)
- Image import/export beyond PNG save
- Layers
- Undo/redo history
- Advanced UI (menus, dialogs, fonts beyond shapes)
- Networked collaboration

## Functional Requirements
- **Window**: Title set to "Paint"; default size around 800x600; uses SFML 3 video mode brace-init.
- **Input**: Left mouse button draws; mouse move while pressed continues stroke; release stops drawing.
- **Brush/Eraser**: Configurable radius and color via state; eraser draws using background color with identical radius.
- **Toolbar**: Right-docked vertical buttons (Brush, Eraser, Clear, Save) with simple shape icons; hover/active states; click to trigger actions.
- **Palette**: Right-docked column beneath toolbar; click swatch to set brush color.
- **State**: Keep strokes in memory (vector) and redraw every frame; background color configurable.
- **Event Handling**: Use SFML 3 `pollEvent()` returning `std::optional<sf::Event>` and `event.is<>()` checks.
- **Clear/Save**: Clear empties stroke buffer; Save writes current canvas to PNG.

## Usability Requirements
- Smooth drawing at 60 FPS on Apple Silicon for simple strokes.
- Minimal latency on mouse down/move.
- Window close event exits cleanly.

## Reliability & Performance
- Avoid dynamic allocations in hot paths when possible (reserve stroke buffers if feasible).
- Keep per-frame work minimal: clear, draw strokes, display.
- No crashes on rapid input or window resize events (ignore resize handling for now).

## Configuration Defaults
- Window size: 800x600
- Background color: White
- Default brush color: Black
- Default brush radius: ~6 px

## Future Enhancements (Post-MVP)
- Toolbar UI for tool selection and color/size changes.
- Eraser tool (draws background color with same radius logic).
- Export canvas to PNG.
- Undo/redo with stroke history.
- Keyboard shortcuts (color cycling, brush size +/-).
- Simple shapes (line/rectangle/ellipse) with drag interactions.

## Acceptance Criteria
- Building with the documented CMake commands succeeds on macOS with SFML 3 installed.
- Launching the app shows the window and allows drawing continuous strokes with the left mouse button using the default brush.
- Strokes persist until explicitly cleared (no unintended clearing between frames).
- Background color matches configured default; brush color and radius match defaults unless changed in code.
- Closing the window exits without errors.
