#include <iostream>
#include <cassert>
#include <string>

using namespace std;

template<typename ItemType>
class HashTable{
    private:
        //pointer to the hash table
        ItemType* HTable;
        //pointer to the array indicating the status of a position in the hash table.
        //1: the position is occupied, 0: the position is empty, -1: the item on this position is removed.
        int* indexStatusList;
        //number of items in the hash table
        int length;
        //maximum size of the hash table
        int HTSize;
    public:
        //Constructor
        //Post-condition: Create the arrays HTable and indexStatusList. Initialize the array indexStatusList to 0, length = 0, HTSize = size
        //The default array size is 101.
        HashTable(int size = 101);
        //Destructor
        //Post-condition: Array HTable and IndexStatusList are deleted.
        ~HashTable();
        //Function to hash the nmae
        int stringHashFunc(string name);
        //Function to insert an item in the hash table
        //The first parameter specifies the initial hash index of the item to be inserted.
        //The item to be inserted is specified by the parameter item.
        //Post-condition: If an empty position is found in the hash table, item is inserted and the length is incremented by one
        //Otherwise, an appropriate error message is displayed.
        void insert(const ItemType& item);
        //Function to determine whether the item specified by the parameter item is in the hash table.
        //The parameter hashIndex specifies the initial hash index of item.
        //Post-condition: If item is found, returns true, else returns false
        bool search(const ItemType& item);
        //Function to determine whether the item specified by the parameter item is the same as the item in the hash table at poistion hashIndex.
        //Post-condition: Returns true if HTable[hashIndex] == item. Otherwise, returns false.
        bool isItemAtIndex(int hashIndex, const ItemType& item) const;
        //Function to retrieve the item at position hashIndex
        //Post-condition: If the table has an item at position hashIndex, it is copied to item.
        void retrieve(int hashIndex, ItemType& item);
        //Function to remove an item from the hash table.
        //Post-condition: Given the initial hashIndex, if item is found in the table, it will be removed.
        //Otherwise, an appropriate error message is displayed.
        void remove(const ItemType& item);
        //Function to output the data.
        void print() const;
};

const int LIST_LENGTH = 6;
const int HT_SIZE = 10;

int main(){
    string nameList[LIST_LENGTH] = {"Apple", "Apple", "Banana", "Cat", "Dog", "Elephant"};
    string apple = "Apples";
    string cat = "Cat";
    string dog = "Dog";
    string temp = "!";
    HashTable<string> HT(HT_SIZE);
    for (int i = 0; i < LIST_LENGTH; i++){
        int hashIndex = HT.stringHashFunc(nameList[i]);
        cout << nameList[i] << " " << hashIndex << endl;
        HT.insert(nameList[i]);
    }
    HT.print();
    HT.remove(cat);
    HT.print();
    HT.retrieve(7, temp);
    cout << temp << endl;
    cout << HT.search(dog) << endl;
    cout << HT.search(cat) << endl;
    cout << HT.isItemAtIndex(5, cat);
    return 0;
}

template <typename ItemType>
HashTable<ItemType>::HashTable(int size){
    HTable = new ItemType[size];
    indexStatusList = new int[size];
    for (int i = 0; i < size; i ++){
        indexStatusList[i] = 0;
    }
    length = 0;
    HTSize = size;
}

template <typename ItemType>
HashTable<ItemType>::~HashTable(){
    delete [] HTable;
    delete [] indexStatusList;
}

template <typename ItemType>
void HashTable<ItemType>::insert(const ItemType& item){
    int probeCount = 0;
    int increment = 1;
    int hashIndex = stringHashFunc(item);
    //probing when
    //1. the position is occupied
    //2. the item inserted is not duplicated
    //3. probeCount is less than HTSize / 2 
    //(we can proved that all item will be inserted when max probe occurrence is less than HTSize/2 as long as we use quadratic probing)
    while(indexStatusList[hashIndex] == 1 && HTable[hashIndex] != item && probeCount < HTSize / 2){
        probeCount++;
        hashIndex = (hashIndex + increment) % HTSize;
        increment = increment + 2;
    }
    if (indexStatusList[hashIndex] != 1){
        HTable[hashIndex] = item;
        indexStatusList[hashIndex] = 1;
        length++;
    }
    else if (HTable[hashIndex] == item){
        cout << "Error: No duplicates are allowed." << endl;
    }
    else{
        cout << "Error: The table if full. Unable to resolve the collision." << endl;
    }
}

template<typename ItemType>
bool HashTable<ItemType>::search(const ItemType& item){
    int probeCount = 0;
    int increment = 1;
    int hashIndex = stringHashFunc(item);
    //probing until we find it (return the correct hashIndex)
    while(HTable[hashIndex] != item && probeCount < HTSize / 2){
        hashIndex = (hashIndex + increment) % HTSize;
        increment = increment + 2;
    }

    if (indexStatusList[hashIndex] != 1){
        //cout << "The item is not in the hash table.";
        return false;
    }
    else{
        return true;
    }
}

template<typename ItemType>
bool HashTable<ItemType>::isItemAtIndex(int hashIndex, const ItemType& item) const{
    // int probeCount = 0;
    // int increment = 1;
    // while(HTable[hashIndex] != item && probeCount < HTSize / 2){
    //     hashIndex = (hashIndex + increment) % HTSize;
    //     increment = increment + 2;
    //     probeCount++;
    // }
    if (HTable[hashIndex] == item){
        return true;
    }
    else{
        return false;
    }

}

template<typename ItemType>
void HashTable<ItemType>::retrieve(int hashIndex, ItemType& item){
    int probeCount = 0;
    int increment = 1;
    if (indexStatusList[hashIndex] == 1){
        item = HTable[hashIndex];
    }
    else{
        cout << "There's no item at this index";
    }
}

template<typename ItemType>
void HashTable<ItemType>::remove(const ItemType& item){
    int probeCount = 0;
    int increment = 1;
    int hashIndex = stringHashFunc(item);
    while(HTable[hashIndex] != item && probeCount < HTSize / 2){
        hashIndex = (hashIndex + increment) % HTSize;
        increment = increment + 2;
        probeCount++;
    }
    if (indexStatusList[hashIndex] == 1){
        indexStatusList[hashIndex] = -1;
    }
    else{
        cout << "The item retrieved is not in the hash table.";
    }   
}

template<typename ItemType>
void HashTable<ItemType>::print() const{
    cout << "Hash table status:" << endl;
    for (int i = 0; i < HTSize; i++){
        cout << i << ": " << HTable[i] << endl;
    }
    cout << "index status:" << endl;
    for (int i = 0; i < HTSize; i++){
        cout << i << ": " << indexStatusList[i] << endl;
    }
}

template <typename ItemType>
int HashTable<ItemType>::stringHashFunc(string name){
    int i = 0;
    int sum = 0;
    int len = name.length();
    for (int k = 0; k < 15 - len; k++){
        //increase the length of the name to 15 characters.
        name = name + ' ';
    }
    for (int k = 0; k < 5; k++){
        sum = sum + static_cast<int>(name[i]) * 128 * 128
                + static_cast<int>(name[i+1]) * 128
                + static_cast<int>(name[i+1]);
        i = i + 3;
    }
    return (sum % HTSize);
}