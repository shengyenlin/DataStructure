#include <iostream>
#include <vector>
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
        void divideList(Node<ItemType>* first1, Node<ItemType>* &first2);
        Node<ItemType>* mergeList(Node<ItemType>* first1, Node<ItemType>* first2);
        void recMergeSort(Node<ItemType>* &head);
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
        void insertionSort();
        void mergeSort();
};

const int ARRAY_LEN = 10;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int main(){
    int arr[ARRAY_LEN] = {1, 7, 15, 9, 3, 4, 2, 5, 10, 0};
    LinkedBag<int> LL;
    for (int i = 0; i < ARRAY_LEN; i++){
        LL.add(arr[i]);
    }
    LL.print();
    //LL.insertionSort();
    LL.mergeSort();
    LL.print();
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

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
    cout << "(";
    while (curPtr->getNext() != nullptr){
        cout << curPtr->getItem() << ", ";
        curPtr = curPtr->getNext();
    }
    cout << curPtr->getItem() << ")";
    cout << endl;
}

template<typename ItemType>
void LinkedBag<ItemType>::insertionSort(){
    Node<ItemType>* lastInOrderPtr;
    Node<ItemType>* firstOutOfOrderPtr;
    Node<ItemType>* curPtr;
    Node<ItemType>* trailCurPtr;

    lastInOrderPtr = headPtr;
    if (headPtr == nullptr){
        cout << "Cannot sort an empty array.";
    }
    else if (headPtr->getNext() == nullptr){
        cout << "The array is of length 1." << endl;
        cout << "It's already in order." << endl;
    }
    else{
        while(lastInOrderPtr->getNext() != nullptr){
            firstOutOfOrderPtr = lastInOrderPtr->getNext();
            //case1: element in firstOutOfOrderPtr is less than the first node
            if (firstOutOfOrderPtr->getItem() < headPtr->getItem()){
                //the last element in order should connect to
                //the next element of firstOutOfOrderPtr
                lastInOrderPtr->setNext(firstOutOfOrderPtr->getNext());
                firstOutOfOrderPtr->setNext(headPtr);
                headPtr = firstOutOfOrderPtr;
            }
            //case2: the element in firstOutOfOrder should be inserted
            //somewhere between two nodes.
            else{
                trailCurPtr = headPtr;
                curPtr = headPtr->getNext();

                while(curPtr->getItem() < firstOutOfOrderPtr->getItem()){
                    trailCurPtr = curPtr;
                    curPtr = curPtr->getNext();
                }
                //the element need to be adjusted
                if (curPtr != firstOutOfOrderPtr){
                    lastInOrderPtr->setNext(firstOutOfOrderPtr->getNext());
                    trailCurPtr->setNext(firstOutOfOrderPtr);
                    firstOutOfOrderPtr->setNext(curPtr);
                }
                //the element do not need to be adjusted
                else{
                    //update the traverse Ptr
                    lastInOrderPtr = lastInOrderPtr->getNext();
                }
            }
        }
    }
}

template<typename ItemType>
void LinkedBag<ItemType>::divideList(Node<ItemType>* first1, Node<ItemType>* &first2){
    Node<ItemType>* middle;
    //curren should be two nodes away from middle when initialized
    Node<ItemType>* current;
    //case1: The list is empty
    if (first1 == nullptr){
        first1 = nullptr;
    }
    //case2: The list has only one element
    else if (first1->getNext() == nullptr){
        first2 = nullptr;
    }
    else{
        middle = first1;
        current = first1->getNext();
        //case3a: The list has more than two nodes
        if (current != nullptr){
            current = current->getNext();
        }
        while (current != nullptr){
            middle = middle->getNext();
            current = current->getNext();
            if (current != nullptr){
                current = current->getNext();
            }
        }
        //first2 points to the first node of the second sublist
        first2 = middle->getNext();
        //set the link of the last node of the first sublist to null
        middle->setNext(nullptr);
    }
}

template <typename ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeList(Node<ItemType>* first1, Node<ItemType>* first2){
    //pointer to the last node of the merged list
    Node<ItemType>* lastMerged;
    //pointer to the merged list
    Node<ItemType>* newHead;
    //case1: the first sublist is empty
    if (first1 == nullptr){
        return first2;
    }
    //case2: the second sublist is empty
    else if (first2 == nullptr){
        return first1;
    }
    else{
        //compare the first node
        //initialize the merged list
        if (first1->getItem() < first2->getItem()){
            newHead = first1;
            first1 = first1->getNext();
            lastMerged = newHead;
        }
        else{
            newHead = first2;
            first2 = first2->getNext();
            lastMerged = newHead;
        }
        //traverse two list until one is empty
        while(first1 != nullptr && first2 != nullptr){
            //compare element of the two list
            if (first1->getItem() < first2->getItem()){
                lastMerged->setNext(first1);
                lastMerged = first1;
                first1 = first1->getNext();
            }
            else{
                lastMerged->setNext(first2);
                lastMerged = first2;
                first2 = first2->getNext();               
            }
        }
        //first list is exhausted
        if (first1 == nullptr){
            lastMerged->setNext(first2);
        }
        else{
            lastMerged->setNext(first1);
        }
    }
    return newHead;
}

template<typename ItemType>
void LinkedBag<ItemType>::recMergeSort(Node<ItemType>* &head){
    Node<ItemType>* otherHead;
    //If the list is not empty
    if (head != nullptr){
        //If the list has more than one node
        if (head->getNext() != nullptr){
            divideList(head, otherHead);
            //cout << head->getItem() << " " << otherHead->getItem() << endl;
            recMergeSort(head);
            recMergeSort(otherHead);
            head = mergeList(head, otherHead);
            //cout << head->getItem() << " " << otherHead->getItem() << endl;
        }
    }
}

template<typename ItemType>
void LinkedBag<ItemType>::mergeSort(){
    recMergeSort(headPtr);
}
