Of course, here is a README file for your project.

-----

# Rubik's Cube Solver

This project is a C++ implementation of a Rubik's Cube solver that can find the solution for a scrambled 3x3x3 cube. It features multiple solving algorithms and cube representations to demonstrate and compare their efficiency.

## Features ✨

  * **Multiple Cube Models**: Includes three different ways to represent the Rubik's Cube internally:
      * **1D Array**: A simple, flat array representing all the stickers.
      * **3D Array**: A more intuitive model using a 3D array for each face.
      * **Bitboard**: A highly optimized model using bitwise operations for maximum speed.
  * **Variety of Solvers**: Implements four different search algorithms to find the solution:
      * **Depth-First Search (DFS)**: A basic recursive solver.
      * **Breadth-First Search (BFS)**: Guarantees the shortest solution but is memory-intensive.
      * **Iterative Deepening DFS (IDDFS)**: A hybrid approach that finds the shortest path with better memory efficiency than BFS.
      * **Iterative Deepening A\* (IDA\*)**: The most advanced solver in this project, which uses a corner pattern database heuristic to find solutions incredibly fast.
  * **Performance Comparison**: The main application runs all solvers on the same scrambled cube and prints the time each one takes, allowing for a clear comparison of their performance.

## Getting Started

Follow these instructions to get the project up and running on your local machine.

### Prerequisites

You will need a C++ compiler and CMake installed on your system to build the project.

### Building and Running

1.  **Clone the repository**:

    ```bash
    git clone https://github.com/your-username/rubiks-cube-solver.git
    cd rubiks-cube-solver
    ```

2.  **Create a build directory**:

    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake and build the project**:

    ```bash
    cmake ..
    make
    ```

4.  **Run the solver**:

    ```bash
    ./rubiks_cube_solver
    ```

Upon running, the program will generate a random scramble, apply it to the cube, and then solve it using each of the four algorithms, printing the solution and timing the results.

## How It Works

The project is structured to separate the cube's data representation from the solving logic.

  * `/Model`: This directory contains the different representations of the Rubik's Cube. The `RubiksCubeBitboard.cpp` is the most optimized version, designed for high-speed operations.
  * `/Solver`: Here, you'll find the implementations of the four solving algorithms. The `IDAstarSolver.h` is the most efficient, thanks to its use of heuristics.
  * `/PatternDatabases`: This contains the code for generating and using the **Corner Pattern Database**. This database pre-calculates the number of moves required to solve the corner pieces of the cube from any position, which allows the IDA\* solver to make much more intelligent decisions and find the solution faster.

The `main.cpp` file acts as the driver, bringing everything together. It first scrambles a cube and then passes it to each solver, showcasing their relative strengths and weaknesses.