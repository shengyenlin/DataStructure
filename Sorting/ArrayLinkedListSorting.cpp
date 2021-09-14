#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename ItemType>
class BagInterface{
    public:
        virtual int getCurrentSize() const = 0;
        virtual bool isEmpty() const = 0;
        virtual void add(const ItemType& newEntry) = 0;
        virtual void remove(const ItemType& newEntry) = 0;
        virtual void clear() = 0;
        virtual int getFrequencyOf(const ItemType& anEntry) const = 0;
        virtual bool contains(const ItemType& anEntry) const = 0;
        virtual void print() const = 0;
};

template<typename ItemType>
class ArrayBag:public BagInterface<ItemType>{
    private:
        static const int DEFAULT_CAPACITY = 100;
        ItemType* items;
        int itemCount;
        int maxItems;
        //Get the index of a specific target
        //If we find it, return index of the target
        //If we don't find it, return -1
        int getIndexOf(const ItemType& target) const;
        //Get the location of minimum element in the array[first:last]
        int getMinLocation(int first, int last);
        //Swap the element int array[first] and array[second]
        void swap(int first, int second);
    public:
        ArrayBag();
        ~ArrayBag();
        int getCurrentSize() const;
        bool isEmpty() const;
        void print() const;
        void add(const ItemType& newEntry);
        //Remove the element of an entry
        //If we don't find the entry, return false
        //Postcondition: The hole of the bag will be fill with the last element of the bag, so the bag won't be empty
        void remove(const ItemType& anEntry);
        void clear();
        int getFrequencyOf(const ItemType& anEntry) const;
        bool contains(const ItemType& anEntry) const;
        void selectionSort();
        void insertionSort();
        void shellSort();
};


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int main(){
    ArrayBag<int> arrayList; 
    //cout << arrayList.getCurrentSize() << endl;
    arrayList.add(90);
    arrayList.add(80);
    arrayList.add(70);
    arrayList.add(60);
    arrayList.add(50);
    arrayList.add(40);
    arrayList.add(30);
    arrayList.add(100);
    arrayList.print();
    //arrayList.insertionSort();
    //arrayList.selectionSort();
    arrayList.shellSort();
    arrayList.print();
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

template<typename ItemType>
ArrayBag<ItemType>::ArrayBag():itemCount(0), maxItems(ArrayBag::DEFAULT_CAPACITY){
    items = new ItemType[DEFAULT_CAPACITY];
}

template<typename ItemType>
ArrayBag<ItemType>::~ArrayBag(){
    delete [] items;
}

template<typename ItemType>
int ArrayBag<ItemType>::getCurrentSize() const{
    return itemCount;
}

template<typename ItemType>
bool ArrayBag<ItemType>::isEmpty() const{
    return itemCount == 0;
}

template<typename ItemType>
void ArrayBag<ItemType>::print() const{
    cout << "(";
    for (int i = 0; i < itemCount - 1; i++){
        cout << items[i] << ", ";
    }
    cout << items[itemCount - 1] << ")";
    cout << endl;
}

template<typename ItemType>
void ArrayBag<ItemType>::add(const ItemType& newEntry){
    bool hasRoomToAdd = (itemCount < maxItems);
    if (!hasRoomToAdd){
        ItemType* oldArray = items;
        items = new ItemType[2 * maxItems];
        for (int i = 0; i < maxItems; i++){
            items[i] = oldArray[i];
        }
        delete [] oldArray;
        maxItems = 2 * maxItems;
    }
    items[itemCount] = newEntry;
    itemCount++;
}


template<typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const{
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

template<typename ItemType>
void ArrayBag<ItemType>::remove(const ItemType& anEntry){
    int locatedIndex = getIndexOf(anEntry);
    bool canRemoveItem = (locatedIndex != -1);
    if (canRemoveItem){
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }
}

template<typename ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const{
    return (getIndexOf(anEntry) != -1);
}

template<typename ItemType>
void ArrayBag<ItemType>::clear(){
    itemCount = 0;
}

template<typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const{
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

template<typename ItemType>
int ArrayBag<ItemType>::getMinLocation(int first, int last){
    int minIndex = first;
    for (int loc = first + 1; loc <= last; loc++){
        if (items[loc] < items[minIndex]){
            minIndex = loc;
        }
    }
    return minIndex;
}

template<typename ItemType>
void ArrayBag<ItemType>::swap(int first, int second){
    ItemType temp = items[first];
    items[first] = items[second];
    items[second] = temp;
}

template<typename ItemType>
void ArrayBag<ItemType>::selectionSort(){
    int minIndex;
    for (int loc = 0; loc < itemCount - 1; loc++){
        minIndex = getMinLocation(loc, itemCount - 1);
        swap(loc, minIndex);
    }
}

template<typename ItemType>
void ArrayBag<ItemType>::insertionSort(){
    int firstOutOfOrder, location;
    ItemType temp;
    for (firstOutOfOrder = 1; firstOutOfOrder < itemCount; firstOutOfOrder++){
        if (items[firstOutOfOrder] < items[firstOutOfOrder - 1]){
            temp = items[firstOutOfOrder];
            location = firstOutOfOrder;
            //move array[location - 1] one array slot down
            //until the element in the upper list at location - 1 is less than that at firstOutOfOrder
            while(location > 0 && items[location - 1] > temp){
                items[location] = items[location - 1];
                location--;
            }
            items[location] = temp;
        }
    }
}

template<typename ItemType>
void ArrayBag<ItemType>::shellSort(){
    int gap = 1;
    //create the largest element in the increment sequences
    while (3 * gap + 1 < itemCount - 1){
        gap = 3 * gap + 1;
    }
    while (gap > 0){
        cout << gap << endl;
        cout << "======================" << endl;
        //interval insertion sort
        for (int i = gap; i <= itemCount - 1; i++){
            int temp = items[i];
            int j = i;
            while (j >= gap && items[j - gap] > temp){
                items[j] = items[j - gap];
                j -= gap;
            }
            items[j] = temp;
        }
        gap = gap / 3;
    }
}