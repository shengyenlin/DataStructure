#include <iostream>
#include <queue>

using namespace std;

int main(){

    queue<int> intQueue;
    intQueue.push(10);
    intQueue.push(30);
    intQueue.push(50);
    intQueue.push(70);
    intQueue.push(90);
    cout << intQueue.back() << endl; //90
    cout << intQueue.front() << endl; //10

    intQueue.pop();
    cout << intQueue.back() << endl; //90
    cout << intQueue.front() << endl; //30

    queue<int> intQueue2 = intQueue;
    while (!intQueue2.empty()){
        cout << intQueue2.front() << " "; //30 50 70 90 
        intQueue2.pop();
    }
    cout << endl;
    cout << intQueue.back() << endl; //90
    cout << intQueue.front() << endl; //30
}