#include <iostream>
#include <string>
using namespace std;

class BagInterface{
    public:
        virtual int getCurrentSize() const = 0;
        virtual bool isEmpty() const = 0;
        virtual bool add(const string& newEntry) = 0;
        virtual bool remove(const string& newEntry) = 0;
        virtual void clear() = 0;
        virtual int getFrequencyOf(const string& anEntry) const = 0;
        virtual bool contains(const string& anEntry) const = 0;
        virtual void print() const = 0;
};

class ArrayBag:public BagInterface{
    private:
        static const int DEFAULT_CAPACITY = 6;
        string* items;
        int itemCount;
        int maxItems;
        //Get the index of a specific target
        //If we find it, return index of the target
        //If we don't find it, return -1
        //Precondition: target is a C++string
        int getIndexOf(const string& target) const;
    public:
        ArrayBag();
        ~ArrayBag();
        int getCurrentSize() const;
        bool isEmpty() const;
        void print() const;
        bool add(const string& newEntry);
        //Remove the element of an entry
        //If we don't find the entry, return false
        //Postcondition: The hole of the bag will be fill with the last element of the bag, so the bag won't be empty
        bool remove(const string& anEntry);
        void clear();
        int getFrequencyOf(const string& anEntry) const;
        bool contains(const string& anEntry) const;
};

int main(){
    ArrayBag bag;
    bag.add("123");
    bag.print();
    cout << bag.isEmpty() << endl;
    cout << bag.getCurrentSize() << endl;
    bag.add("bbb");
    bag.print();
    cout << bag.getCurrentSize() << endl;
    return 0;
}

ArrayBag::ArrayBag():itemCount(0), maxItems(ArrayBag::DEFAULT_CAPACITY){
    items = new string[DEFAULT_CAPACITY];
}

ArrayBag::~ArrayBag(){
    delete [] items;
}

int ArrayBag::getCurrentSize() const{
    return itemCount;
}

bool ArrayBag::isEmpty() const{
    return itemCount == 0;
}

void ArrayBag::print() const{
    for (int i = 0; i < itemCount; i++){
        cout << items[i] << " ";
    }
    cout << endl;
}

bool ArrayBag::add(const string& newEntry){
    bool hasRoomToAdd = (itemCount < maxItems);
    if (!hasRoomToAdd){
        string* oldArray = items;
        items = new string[2 * maxItems];
        for (int i = 0; i < maxItems; i++){
            items[i] = oldArray[i];
        }
        delete [] oldArray;
        maxItems = 2 * maxItems;
    }
    items[itemCount] = newEntry;
    itemCount++;
    return true;
}

bool ArrayBag::remove(const string& newEntry){
    return 0;
}
void ArrayBag::clear(){

}
int ArrayBag::getFrequencyOf(const string& anEntry) const{
    return 0;
}
bool ArrayBag::contains(const string& anEntry) const{
    return 0;
}

int ArrayBag::getIndexOf(const string& target) const{
    bool found = false;
    int result = -1;
    int searchIndex = 0;
    //linear search
    while(!found && (searchIndex < itemCount)){
        if(items[searchIndex] == target){
            found = true;
            result = searchIndex;
        }
        else{
            searchIndex++;
        }
    }
    return result;
}

bool ArrayBag::remove(const string& anEntry){
    int locatedIndex = getIndexOf(anEntry);
    bool canRemoveItem = (locatedIndex != -1);
    if (canRemoveItem){
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }
    return canRemoveItem;
}

bool ArrayBag::contains(const string& anEntry) const{
    return (getIndexOf(anEntry) != -1);
}

void ArrayBag::clear(){
    itemCount = 0;
}

int ArrayBag::getFrequencyOf(const string& anEntry) const{
    int frequency = 0;
    int curIndex = 0;
    while(curIndex < itemCount){
        if(items[curIndex] == anEntry){
            frequency++;
        }
        curIndex++;
    }
    return frequency;
}