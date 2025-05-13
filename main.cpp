#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define ROWS 50
#define COLS 50

void init_grid(int** grid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

void print_grid(int** grid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << (grid[i][j] ? "\u2588" : " "); // █ - U+2588
        }
        cout << endl;
    }
}

void next_gen(int** grid) {
    int next_grid[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbours = 0;
            // x-axis and y-axis neighbours
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) { continue; }
                    int ni = i + x;
                    int nj = j + y;

                    // handle wrap-around conditions also
                    if (ni < 0) { ni = ROWS - 1; }
                    if (ni >= ROWS) { ni = 0; }
                    if (nj < 0) { nj = COLS - 1; }
                    if (nj >= COLS) { nj = 0; }
                    neighbours += grid[ni][nj];
                }
            }
            // Apply the rules of Conway's Game of Life
            if (grid[i][j]) { // if it is a live cell
                if (neighbours < 2 || neighbours > 3) {
                    next_grid[i][j] = 0;
                } else {
                    next_grid[i][j] = 1;
                }
            } else {
                if (neighbours == 3) {
                    next_grid[i][j] = 1; // new cell born
                } else {
                    next_grid[i][j] = 0;
                }
            }
        }
    }
    // Copy back to original grid
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = next_grid[i][j];
        }
    }
}

int main() {
    // create the grid
    int** grid = new int*[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        grid[i] = new int[COLS];
    }
    
    // random number generator to initialize the grid
    srand(time(NULL));
    init_grid(grid);
    
    int generations = 10;
    for (int i = 0; i < generations; ++i) {
        cout << "Generation " << i + 1 << " : " << endl;
        print_grid(grid);
        next_gen(grid);
        
        // Add a prompt to see the generations
        cout << "\nPress Enter for next generation...";
        cin.get();
    }
    
    // Free allocated memory
    for (int i = 0; i < ROWS; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    
    return 0;
}
