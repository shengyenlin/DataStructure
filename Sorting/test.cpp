#include <iostream>

using namespace std;

void func2(int* Ptr1, int* Ptr2){
    Ptr1 = Ptr2;
};

void func1(int* &Ptr1, int* &Ptr2){
    func2(Ptr1, Ptr2);
};

int main(){
    int a = 5;
    int b = 10;
    int* aPtr = &a;
    int* bPtr = &b;
    func1(aPtr, bPtr);
    cout << *aPtr;
    return 0;
}