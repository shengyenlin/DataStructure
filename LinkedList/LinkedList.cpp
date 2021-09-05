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
        void add(const string& newEntry);
        //Remove the element of an entry
        //If we don't find the entry, return false
        //Postcondition: The hole of the bag will be fill with the last element of the bag, so the bag won't be empty
        void remove(const string& anEntry);
        void clear();
        int getFrequencyOf(const string& anEntry) const;
        bool contains(const string& anEntry) const;
};


template<typename ItemType>
class Node{
    private:
        ItemType item;
        Node<ItemType>* next;
    public:
        Node();
        Node(const ItemType& anItem);
        Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
        void setItem(const ItemType& anItem);
        void setNext(Node<ItemType>* nextNodePtr);
        ItemType getItem() const;
        Node<ItemType>* getNext() const;
};

template<typename ItemType>
class LinkedBag:public BagInterface<ItemType>{
    private:
        Node<ItemType>* headPtr;
        int itemCount;
        Node<ItemType>* getPointerTo(const ItemType& anEntry) const;
    public:
        LinkedBag();
        LinkedBag(const LinkedBag<ItemType>& aBag);
        //make sure that if there's a child of this class
        //the destructor of child class will be called
        virtual ~LinkedBag();
        bool contains(const ItemType& anEntry) const;
        bool isEmpty() const;
        int getCurrentSize() const;
        int getFrequencyOf(const ItemType& anEntry) const;
        void add(const ItemType& newEntry); 
        void remove(const ItemType& anEntry);
        void clear();
        void print() const;
        vector<ItemType> toVector();
};

void testBag(BagInterface<string>* bagPtr);

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int main(){
    BagInterface<string>* bagPtr = nullptr;
    char userChoice = 0;
    cin >> userChoice;
    if (userChoice == 'A'){
        bagPtr = new ArrayBag<string>();
    }
    else{
        bagPtr = new LinkedBag<string>();
    }
    testBag(bagPtr);
    delete bagPtr;
    bagPtr = nullptr;
    return 0;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

template<typename ItemType>
ArrayBag<ItemType>::ArrayBag():itemCount(0), maxItems(ArrayBag::DEFAULT_CAPACITY){
    items = new string[DEFAULT_CAPACITY];
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
    for (int i = 0; i < itemCount; i++){
        cout << items[i] << " ";
    }
    cout << endl;
}

template<typename ItemType>
void ArrayBag<ItemType>::add(const string& newEntry){
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
}


template<typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const string& target) const{
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
void ArrayBag<ItemType>::remove(const string& anEntry){
    int locatedIndex = getIndexOf(anEntry);
    bool canRemoveItem = (locatedIndex != -1);
    if (canRemoveItem){
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }
}

template<typename ItemType>
bool ArrayBag<ItemType>::contains(const string& anEntry) const{
    return (getIndexOf(anEntry) != -1);
}

template<typename ItemType>
void ArrayBag<ItemType>::clear(){
    itemCount = 0;
}

template<typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const string& anEntry) const{
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
Node<ItemType>::Node():next(nullptr){}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem):item(anItem), next(nullptr){}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):
    item(anItem), next(nextNodePtr){}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
    item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
    next = nextNodePtr;
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const{
    return item;
}

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
    return next;
};

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag():headPtr(nullptr), itemCount(0){}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag){
    itemCount = aBag->itemCount;
    //the pointer running on the old chain
    Node<ItemType>* origChainPtr = aBag->headPtr;
    if (origChainPtr == nullptr){
        headPtr = nullptr;
    }
    else{
        headPtr = new Node<ItemType>;
        headPtr->setItem(origChainPtr->getItem());
        //the pointer running on the new chain
        Node<ItemType>* newChainPtr = headPtr;
        while(origChainPtr != nullptr){
            origChainPtr = origChainPtr->getNext();
            ItemType nextItem = origChainPtr->getItem();
            Node<ItemType>* newNodePtr = Node<ItemType>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
        }
        //running into the end of the nwe chain pointer
        //since the final "setNext" won't set a nullptr
        //we need to set it manually
        //but i thinks it's useless since we set next pointer to nullptr
        //when we initialize the newNode with nextItem 
        newChainPtr->setNext(nullptr);
    }
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag(){
    clear(); 
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const{
    return (itemCount == 0);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const{
    return itemCount;
}

template<typename ItemType>
void LinkedBag<ItemType>::add(const ItemType& newEntry){
    Node<ItemType>* newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCount++;
}

template<typename ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector(){
    vector<ItemType> bagContents;
    Node<ItemType>* curPtr = headPtr;
    while(curPtr != nullptr){
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
    }
    return bagContents;
}

template<typename ItemType>
void LinkedBag<ItemType>::remove(const ItemType& anEntry){
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if (canRemoveItem){
        entryNodePtr->setItem(headPtr->getItem());
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        //wrong implementation: headPtr wo't find anything after delete statement
        // delete headPtr;
        // headPtr = headPtr->getNext();
        itemCount--;
    }
}

template<typename ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const{
    bool found = false;
    Node<ItemType>* curPtr = headPtr;
    while(!found && (curPtr != nullptr)){
        if(anEntry == curPtr->getItem()){
            found = true;
        }
        else{
            curPtr = curPtr->getNext();
        }
    }
    return curPtr;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const{
    return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const{
    int frequency = 0;
    Node<ItemType>* curPtr = headPtr;
    while(curPtr!=nullptr){
        if(anEntry == curPtr->getItem()){
            frequency++;
        }
        curPtr = curPtr->getNext();
    }
    return frequency;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear(){
    Node<ItemType>* nodeToDeletePtr = headPtr;
    while(headPtr != nullptr){
        headPtr = headPtr->getNext();
        delete nodeToDeletePtr;
        nodeToDeletePtr = headPtr;
    }
    itemCount = 0;
}

template<typename ItemType>
void LinkedBag<ItemType>::print() const{
    Node<ItemType>* curPtr = headPtr;
    while (curPtr != nullptr){
        cout << curPtr->getItem() << " ";
        curPtr = curPtr->getNext();
    }
    cout << endl;
}

void testBag(BagInterface<string>* bagPtr){
    string items [] = {"aa", "bb", "cc"};
    for (int i = 0; i < 3; i++){
        bagPtr->add(items[i]);
    }
    cout << bagPtr->isEmpty() << " ";
    cout << bagPtr->getCurrentSize() << " ";
    bagPtr->print();
    bagPtr->remove("cc");
    cout << bagPtr->isEmpty() << " ";
    cout << bagPtr->getCurrentSize() << " ";
    bagPtr->print();
}