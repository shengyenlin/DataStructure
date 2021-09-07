#include <iostream>

using namespace std;

class nQueenPuzzle{
    private:
        //number of solutions
        int noOfSolutions;
        //number of queens
        int noOfQueens;
        int* queensInRow;
    public:
        /*Constructor
        @post: noOfSolutions = 0, noOfQueens = queens
               queensInRow is a pointer which points to the 
               array to store the n-tuple
        */
        nQueenPuzzle(int queens = 8);
        /*Function to determine whether a queen can be placed in row k and column i
        @post: return true if a queen can be placed in row k and column i, otherwise false
        */
        bool canPlaceQueen(int k, int i);
        /*Function to determine the solution to the n-queens puzzle using backtracking
        The function is called with the value 0.
        @post: all n-tuples representing solutions of n-queens puzzle are generated and printed.
        */
        void queensConfiguration(int k);
        /*Function to output an n-tuple containing a solution to the n-queens puzzle
        */
        void printConfiguration();
        /*Function to return the total number of solutions
        @post: The value of noOfSolution is returned
        */
        int getSolutionsCount();
        /*Function to solve the puzzle and print configuration
        */
        void solvePuzzle();
};

int main(){
    nQueenPuzzle puzzle(5);
    puzzle.solvePuzzle();
    return 0;
}

nQueenPuzzle::nQueenPuzzle(int queens){
    noOfQueens = queens;
    queensInRow = new int[noOfQueens];
    noOfSolutions = 0;
}

bool nQueenPuzzle::canPlaceQueen(int k, int i){
    for (int j = 0; j < k; j++){
        //someone is on the same column or
        //is on the diagonal line
        if((queensInRow[j] == i) || (abs(queensInRow[j] - i) == abs(j - k)) ){
            return false;
        }
    }
    return true;
}

void nQueenPuzzle::queensConfiguration(int k){
    for (int i = 0; i < noOfQueens; i++){
        if (canPlaceQueen(k, i)){
            //place the kth queen in column i
            queensInRow[k] = i;
            //all the queens are placed
            if (k == noOfQueens - 1){
                printConfiguration();
            }
            //determine the place of the (k+1) queen
            else{
                queensConfiguration(k + 1);
            }
        }
    }
}

void nQueenPuzzle::printConfiguration(){
    noOfSolutions++;
    cout << "(";
    for (int i = 0; i < noOfQueens - 1; i++){
        cout << queensInRow[i] << ", ";
    }
    cout << queensInRow[noOfQueens-1] << ")" << endl;
}

int nQueenPuzzle::getSolutionsCount(){
    return noOfSolutions;
}

void nQueenPuzzle::solvePuzzle(){
    //start from the 0-th queen
    queensConfiguration(0);
}