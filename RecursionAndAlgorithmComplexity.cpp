#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*Computes the factorial of the nonnegative integer n.
@pre n must be greater than or equal to 0.
@post None.
@return The factorial of n; n is unchanged.
*/
int fact(int n){
    //base case
    if (n == 0){
        return 1;
    }
    else{
        return n * fact(n-1);
    }
}

/*Computes the number of groups of k out of n things.
@pre n and k are nonnegative integers.
@post None.
@param n The given number of things
@param k The given number to choose
@return g(n, k)*/
int g(int n, int k){
    if ((k == 0) || (k == n)){
        return 1;
    }
    else if (k > n){
        return 0;
    }
    else{
        return g(n-1, k-1) + g(n-1, k);
    }
}

int main(){
    cout << fact(7) << endl;
    cout << g(10, 3) << endl;
    return 0;
}