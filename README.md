Game of Life — SFML Implementation

Description:
This program implements Conway’s Game of Life using SFML for graphics and input handling.
Each cell on the grid can be alive or dead, and the state updates according to the classic rules:
- A live cell stays alive if it has 2 or 3 live neighbors.
- A dead cell becomes alive if it has exactly 3 live neighbors.
- Otherwise, the cell dies or remains dead.

Features:
- Pause and resume simulation with the Space key.
- Toggle the state of a cell by clicking it with the left mouse button.
- Clear the grid with the C key.
- Randomize the grid with the R key.
- Fullscreen mode at 1920x1080 resolution.
- Frame rate limited to 60 FPS.

Controls:
- Left mouse button — toggle cell state.
- Space — pause/resume simulation.
- C — clear the grid.
- R — randomize the grid.
- Esc or window close — exit the program.

Build:
Requires SFML 2.x installed.
Example compile command (g++):

g++ -std=c++17 main.cpp -o GameOfLife -lsfml-graphics -lsfml-window -lsfml-system

Run:
Execute the compiled binary. The simulation starts paused by default.
