#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){
    //list is the same as a doubly linked list
    list<int> intList1, intList2;
    ostream_iterator<int> screen(cout, " ");
    intList1.push_back(10);
    intList1.push_back(13);
    intList1.push_back(13);
    intList1.push_back(5);
    intList1.push_back(20);
    intList1.push_back(20);
    copy(intList1.begin(), intList1.end(), screen);//10 13 13 5 20 20
    cout << endl;

    //deep copy a list
    intList2 = intList1;
    //remove depulicates in list
    intList1.unique();
    copy(intList1.begin(), intList1.end(), screen); //10 13 5 20
    cout << endl;

    //sort a list
    intList2.sort();
    copy(intList2.begin(), intList2.end(), screen); //5 10 13 13 20 20
    cout << endl;
    return 0;
}