#include <iostream>

using namespace std;

class Sudoku{
    private:
        int grid[9][9];
    public:
        /*Default constructor
        @post: grid is initialized to zero.
        */
        Sudoku();
        /*Constructor
        @post: grid = 9;
        */
        Sudoku(int g[][9]);
        /*Function to print the sudoku grid
        */
        void printSudokuGrid();
        /*Function to solve the sudoku problem
        @post: If a solution exists, returns true, otherwise return false
        */
        bool solveSudoku();
        /*Function to determine if the grid slot specified by row and column is empty
        @post: Return true if grid[row][col] = 0
        */
        bool findEmptyGridSlot(int& row, int& col);
        /*Function to determine if num can be placed in grid[row][col]
        @post: Return true if num can be placed in grid[row][col], otherwise return false
        */
        bool canPlaceNum(int row, int col, int num);
        /*Function to determine if num is in grid[row][]
        @post: Return ture if num is in grid[row][], otherwise return false
        */
        bool numAlreadyInRow(int row, int num);
        /*Function to determine if num is in grid[][col]
        @post: Return true if num is in grid[][col], otherwise return false
        */
        bool numAlreadyInCol(int col, int num);
        /*Function to determine if num is in small grid
        @post: Return true if num is in small grid, otherwise return false.
        */
        bool numAlreadyInBox(int smallGridRow, int smallGridCol, int num);
};

int main(){
	int grid[9][9] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
					{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
					{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
					{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
					{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
					{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
					{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    Sudoku sudoku(grid);
    // sudoku.printSudokuGrid();
    if (sudoku.solveSudoku() == true){
        sudoku.printSudokuGrid();
    }
    else{
        cout << "No solution exists!";
    }
    return 0;
}

Sudoku::Sudoku(){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            grid[row][col] = 0;
        }
    }
}

Sudoku::Sudoku(int g[][9]){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            grid[row][col] = g[row][col];
        }
    }
}

bool Sudoku::solveSudoku(){
    int row, col;
    //row and col will increase in this function
    //there are no empty slots
    if (!findEmptyGridSlot(row, col)){
        return true;
    }
    else{
        // printSudokuGrid();
        // cout << endl;
        for (int num = 1; num <= 9; num++){
            //cout << row << " " << col << " " << num <<endl;
            if (canPlaceNum(row, col, num)){
                //make tentative assignment
                grid[row][col] = num;
                //recursive call
                if (solveSudoku()){
                    return true;
                }
                //dead end, unmake and try again
                grid[row][col] = 0;
            }
        }
        return false; //backtrack
    }
}

bool Sudoku::findEmptyGridSlot(int& row, int& col){
    for (row = 0; row < 9; row++){
        for (col = 0; col < 9; col++){
            // cout << row << " " << col << " " << endl;
            if(grid[row][col] == 0){
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::numAlreadyInRow(int row, int num){
    for (int col = 0; col < 9; col++){
        if (grid[row][col] == num){
            return true;
        }
    }
    return false;
}

bool Sudoku::numAlreadyInCol(int col, int num){
    for (int row = 0; row < 9; row++){
        if (grid[row][col] == num){
            return true;
        }
    }
    return false;
}

bool Sudoku::numAlreadyInBox(int smallGridRow, int smallGridCol, int num){
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            if(grid[smallGridRow+row][smallGridCol+col] == num){
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::canPlaceNum(int row, int col, int num){
    return (!numAlreadyInRow(row, num)) && (!numAlreadyInCol(col, num)) && (!numAlreadyInBox(row - row % 3, col - col % 3, num)) && (grid[row][col] == 0);
}

void Sudoku::printSudokuGrid(){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}