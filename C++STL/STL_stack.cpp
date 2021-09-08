#include <iostream>
#include <stack>

using namespace std;

int main(){
    
    stack<int> intStack;
    intStack.push(16);
    intStack.push(8);
    intStack.push(20);
    intStack.push(3);

    cout << intStack.top() << endl;
    intStack.pop();
    while (!intStack.empty()){
        cout << intStack.top() << endl;
        intStack.pop();
    }
    return 0;
}