#include <bits/stdc++.h>
// Include the cube model you want to use (Bitboard is the fastest)
#include "Model/RubiksCubeBitboard.cpp"

// Include the solver you want to use
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"

using namespace std;
// Function to check if a file exists
bool file_exists(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}
// A helper function to print a solution
void print_solution(const string& solver_name, const vector<RubiksCube::MOVE>& moves) {
    cout << "\n--- " << solver_name << " Solution ---" << endl;
    cout << "Found in " << moves.size() << " moves:" << endl;
    for (auto move : moves) {
        cout << RubiksCube::getMove(move) << " ";
    }
    cout << "\n-----------------------------\n" << endl;
}
int main() {
    string fileName = R"(C:\Users\Jhakas\Desktop\rubiks-cube-solver-main\Databases\cornerDepth5V1.txt)";

    if (!file_exists(fileName)) {
        cout << "FATAL ERROR: Database file not found at '" << fileName << "'." << endl;
        cout << "Please check the path. The program will now exit." << endl;
        return 1; // Exit if the database is missing
    }

    // 1. Create a cube object
    RubiksCubeBitboard cube;
    // You can change the number to make the scramble longer or shorter
    int scramble_depth=6;
    int suffle=5;

    // 2. Scramble the cube
    cout << "\nApplying "<<scramble_depth<<" random scramble..." << endl;
    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(suffle);

    cout << "Scrambled with: ";
    for (auto move: shuffle_moves) {
        cout << RubiksCubeBitboard::getMove(move) << " ";
    }
    cout << "\n\nScrambled Cube State:" << endl;
    cube.print();

    // 1. Solve using IDA* Solver -> FASTEST
    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idaStarSolver(cube, fileName);
    auto start_idstar = chrono::high_resolution_clock::now();
    vector<RubiksCube::MOVE> ida_solution = idaStarSolver.solve();
    auto end_idstar = chrono::high_resolution_clock::now();
    auto duration_idstar = chrono::duration_cast<chrono::milliseconds>(end_idstar - start_idstar);
    cout << "IDA* took: " << duration_idstar.count() << " milliseconds" << endl;
    print_solution("IDA*", ida_solution);

    // 2. Solve using IDDFS Solver
    IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, scramble_depth);
    auto start_iddfs = chrono::high_resolution_clock::now();
    vector<RubiksCube::MOVE> iddfs_solution = iddfsSolver.solve();
    auto end_iddfs = chrono::high_resolution_clock::now();
    auto duration_iddfs = chrono::duration_cast<chrono::milliseconds>(end_iddfs - start_iddfs);
    cout << "IDDFS took: " << duration_iddfs.count() << " milliseconds" << endl;
    print_solution("IDDFS", iddfs_solution);

    // 3. Solve using DFS Solver
    DFSSolver<RubiksCubeBitboard, HashBitboard> dfsSolver(cube, scramble_depth);
    auto start_dfs = chrono::high_resolution_clock::now();
    vector<RubiksCube::MOVE> dfs_solution = dfsSolver.solve();
    auto end_dfs = chrono::high_resolution_clock::now();
    auto duration_dfs = chrono::duration_cast<chrono::milliseconds>(end_dfs - start_dfs);
    cout << "DFS took: " << duration_dfs.count() << " milliseconds" << endl;
    print_solution("DFS", dfs_solution);

    // 4. Solve using BFS Solver
    BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
    auto start_bfs = chrono::high_resolution_clock::now();
    vector<RubiksCube::MOVE> bfs_solution = bfsSolver.solve();
    auto end_bfs = chrono::high_resolution_clock::now();
    auto duration_bfs = chrono::duration_cast<chrono::milliseconds>(end_bfs - start_bfs);
    cout << "BFS took: " << duration_bfs.count() << " milliseconds" << endl;
    print_solution("BFS", bfs_solution);

    return 0;
}