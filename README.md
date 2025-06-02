# 🌱 Life

**Life** is a C++ implementation of Conway's Game of Life, a cellular automaton devised by mathematician John Conway. This simulation demonstrates how complex patterns can emerge from simple rules applied to a grid of cells.

## 🎮 Features

- **Interactive Simulation**: Observe how patterns evolve over time based on initial configurations.
- **Customizable Grid**: Modify the grid size and initial state to explore different scenarios.
- **Performance Optimized**: Efficient algorithms ensure smooth simulations even on larger grids.

## 🧩 How It Works

The Game of Life operates on a two-dimensional grid of cells, each of which can be in one of two states: alive or dead. The state of each cell evolves over discrete time steps according to the following rules:

1. **Underpopulation**: A live cell with fewer than two live neighbors dies.
2. **Survival**: A live cell with two or three live neighbors lives on to the next generation.
3. **Overpopulation**: A live cell with more than three live neighbors dies.
4. **Reproduction**: A dead cell with exactly three live neighbors becomes a live cell.

These simple rules lead to a rich variety of behaviors and patterns.

## 🛠️ Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later (e.g., `g++`, `clang++`)

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone https://github.com/SigmaGit1eR/Life.git
   cd Life
2. **Compile the source code**:
   ```bash
   g++ -std=c++11 main.cpp -o life
3. **Run the simulation**:
   ```bash
   ./life
