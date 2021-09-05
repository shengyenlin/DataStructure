#include <iostream>
#include <cassert>

using namespace std;

template<typename ItemType>
class Node{
    private:
        ItemType item;
        Node<ItemType>* back;
        Node<ItemType>* next;
    public:
        Node();
        Node(const ItemType& anItem);
        Node(const ItemType& anItem, Node<ItemType>* nextNodePtr, Node<ItemType>* backNodePtr);
        void setItem(const ItemType& anItem);
        void setBack(Node<ItemType>* backNodePtr);
        void setNext(Node<ItemType>* nextNodePtr);
        ItemType getItem() const;
        Node<ItemType>* getBack() const;
        Node<ItemType>* getNext() const;
};

template<typename ItemType>
class DoublyLinkedList{
    private:
        int count;
        //pointer points to the first node
        Node<ItemType>* firstPtr;
        //pointer points to the last node
        Node<ItemType>* lastPtr;
        /*Function to make a copy of other list
        @post: A copy of otherList is created and assigned to this list
        */
        void copyList(const DoublyLinkedList<ItemType>& otherList);
    public:
        /*Default constructor
        Initiliaze the list to an empty state
        @post: firstPtr = nullptr, lastPtr = nullptr, count = 0
        */
        DoublyLinkedList();
        /*Copy constructor
        */
        DoublyLinkedList(const DoublyLinkedList<ItemType>& otherList);
        /*Destructor
        @post: the list of object is destroyed.
        */
        ~DoublyLinkedList();
        /*Function to overload the assignment operator
        */
        const DoublyLinkedList<ItemType>& operator= (const DoublyLinkedList<ItemType>& otherList);
        /*Function to initialized the list to an empty state
        @post: firstPtr = nullptr, lastPtr = nullptr, count = 0
        */
        void initializeList();
        /*Function to determine whether the list is empty
        @post: returns true if the list is empty, otherwise false
        */
        bool isEmpty() const;
        /*Function to output the data contained in the linked list
        */
        void print() const;
        /*Function to ouput the info contained in each node in reverse order.
        */
        void reversePrint() const;
        /*Function to delete all the nodes from the list
        @post: first = nullptr, last = nullptr, count = 0
        */
        void destroyList();
        /*Function to return the number of nodes in the list
        */
        int getLength() const;
        /*Function to return the first element of the list
        @pre: the list must exist and is not empty
        @post: if the list is empty, the program terminates
               otherwise, the first element of list is returned
        */
        ItemType getFront() const;
        /*Function to return the last element of the list
        @pre: the list must exist and is not empty
        @post: if the list is empty, the program terminates
               otherwise, the last element of list is returned
        */
        ItemType getBack() const;
        /*Function to determine whether searchItem is in the list
        @post: return true if searchItem is in the list, otherwise false
        */
        bool search(const ItemType& searchItem) const;
        /*Function to insert newItem in the list/
        @post: first pointer point to the new list, newItem is inserted at
        the proper place in the list, count is incremented by 1.
        */
        void insert(const ItemType& newItem);
        /*Function to delete deleteItem from the list
        @post: If found, the node containing deleteItem is deleted from
        the list.
        First pointer points to the first node, last pointer points to
        the last node of the updated list, and count is decremented by 1
        */
        void deleteNode(const ItemType& deleteItem);
};

int main(){
    DoublyLinkedList<int> DLL;
    DLL.insert(10);
    DLL.insert(-5);
    DLL.print(); //-5 10
    DLL.insert(30);
    DLL.insert(-5);
    DLL.print(); //-5 -5 10 30

    DoublyLinkedList<int> DLL2(DLL);

    DLL.deleteNode(10); 
    DLL.print(); //-5 -5 30
    DLL.deleteNode(-5);
    DLL.print(); //-5 30
    DLL.deleteNode(20); //The item to be deleted is not in the list.
    DLL.deleteNode(30); //-5
    DLL.print();

    DLL2.print(); //-5 -5 10 30
    return 0;
}

template<typename ItemType>
Node<ItemType>::Node():next(nullptr), back(nullptr){}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem):item(anItem), next(nullptr), back(nullptr){}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr, Node<ItemType>* backNodePtr):
    item(anItem), next(nextNodePtr), back(backNodePtr){}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
    item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setBack(Node<ItemType>* backNodePtr){
    back = backNodePtr;
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
Node<ItemType>* Node<ItemType>::getBack() const{
    return back;
}

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
    return next;
}

template<typename ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList():
    firstPtr(nullptr), lastPtr(nullptr), count(0){}

template<typename ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList(){
    this->destroyList();
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::initializeList(){
    this->destroyList();
}

template<typename ItemType>
int DoublyLinkedList<ItemType>::getLength() const{
    return count;
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::print() const{
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    curPtr = this->firstPtr;
    while(curPtr!=nullptr){
        cout << curPtr->getItem() << " ";
        curPtr = curPtr->getNext();
    }
    cout << endl;
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::reversePrint() const{
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    curPtr = this->lastPtr;
    while(curPtr!=nullptr){
        cout << curPtr->getItem() << " ";
        curPtr = curPtr->getBack();
    }
}

template<typename ItemType>
bool DoublyLinkedList<ItemType>::search(const ItemType& searchItem) const{
    bool found = false;
    Node<ItemType>* curPtr;
    curPtr = this->firstPtr;
    while(curPtr!=nullptr && !found){
        if (curPtr->getItem() == searchItem){
            found = true;
        }
        else{
            curPtr = curPtr->getNext();
        }
    }
    return found;
}

template<typename ItemType>
ItemType DoublyLinkedList<ItemType>::getFront() const{
    //if the list is empty, the assert statement terminates the program
    assert(this->firstPtr != nullptr);
    return (this->firstPtr->getItem());
}

template<typename ItemType>
ItemType DoublyLinkedList<ItemType>::getBack() const{
    //if the list is empty, the assert statement terminates the program
    assert(this->lastPtr != nullptr);
    return (this->lastPtr->getItem());
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::insert(const ItemType& insertItem){
    Node<ItemType>* curPtr;
    Node<ItemType>* trailCurPtr;
    Node<ItemType>* newNode;
    bool found;

    //create the node
    newNode = new Node<ItemType>;
    newNode->setItem(insertItem);
    newNode->setNext(nullptr);
    newNode->setBack(nullptr);

    //case1: the list is empty
    if (this->firstPtr == nullptr){
        this->firstPtr = newNode;
        this->lastPtr = newNode;
        this->count++;
    }
    else{
        found = false;
        curPtr = this->firstPtr;
        while(curPtr!=nullptr && !found){
            if (curPtr->getItem() >= insertItem){
                found = true;
            }
            else{
                trailCurPtr = curPtr;
                curPtr = curPtr->getNext();
            }
        }
        //insert at beginning
        if (curPtr == this->firstPtr){
            this->firstPtr->setBack(newNode);
            newNode->setNext(this->firstPtr);
            this->firstPtr = newNode;
            this->count++;
        }
        //insert node between trailCurPtr and curPtr
        else{
            if (curPtr != nullptr){
                trailCurPtr->setNext(newNode);
                newNode->setBack(trailCurPtr);
                newNode->setNext(curPtr);
                curPtr->setBack(newNode);
            }
            //insert node at the end
            else{
                trailCurPtr->setNext(newNode);
                newNode->setBack(trailCurPtr);
                this->lastPtr = newNode;
            }
        }
    }
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::deleteNode(const ItemType& deleteItem){
    Node<ItemType>* curPtr;
    Node<ItemType>* trailCurPtr;
    bool found;
    //case1: empty list
    if (this->firstPtr == nullptr){
        cout << "Cannot delete from an empty list" << endl;
    }
    //case2: node to be deleted is the first node
    else if (this->firstPtr->getItem() == deleteItem){
        curPtr = this->firstPtr;
        this->firstPtr = this->firstPtr->getNext();
        //there are more than two nodes in the list
        if (this->firstPtr != nullptr){
            this->firstPtr->setBack(nullptr);
        }
        //there's only one node in the list
        else{
            this->lastPtr = nullptr;
        }
        this->count--;
        delete curPtr;
    }
    //case3: node to be deleted is in the middle of the list
    else{
        found = false;
        curPtr = this->firstPtr;
        while(curPtr != nullptr && !found){
            if (curPtr->getItem() >= deleteItem){
                found = true;
            }
            else{
                trailCurPtr = curPtr;
                curPtr = curPtr->getNext();
            }
        }
        if (curPtr == nullptr){
            cout << "The item to be deleted is not in the list." << endl;
        }
        //check for equality
        else if (curPtr->getItem() == deleteItem){
            trailCurPtr->setNext(curPtr->getNext());
            //case3: deleted item is not the last node
            if (curPtr->getNext() != nullptr){
                curPtr->getNext()->setBack(trailCurPtr);
            }
            //case4: deleted item is the last node
            if (curPtr == this->lastPtr){
                this->lastPtr = trailCurPtr;
            }
            this->count--;
            delete curPtr;
        }
        else{
            cout << "The item to be deleted is not in the list." << endl;
        }
    }
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::copyList(const DoublyLinkedList<ItemType>& otherList){
    //pointer to create node
    Node<ItemType>* newNode;
    //pointer to traverse the list
    Node<ItemType>* curNode;
    if (this->firstPtr != nullptr){
        this->destroyList();
    }
    //if other list is empty
    if(otherList.firstPtr == nullptr){
        this->firstPtr = nullptr;
        this->lastPtr = nullptr;
        count = 0;
    }
    else{
        curNode = otherList.firstPtr;
        count = otherList.count;

        //how to copy the whole list
        //1. create new node
        //2. set the value of this node
        //3. set the pointer of this node to null
        //4. set the "next" pointer of the last node (which is the node before new node) to the new node
        //5. set the last pointer (of the whole new linked list) to this node

        //copy the first node
        firstPtr = new Node<ItemType>;
        firstPtr->setItem(curNode->getItem());
        firstPtr->setNext(nullptr);
        firstPtr->setBack(nullptr);
        lastPtr = firstPtr;  //make last ptr to the first node
        curNode = curNode->getNext();

        //copy the remaining list
        while(curNode != nullptr){
            //create and copy information
            newNode = new Node<ItemType>;
            newNode->setItem(curNode->getItem());
            newNode->setNext(nullptr);
            newNode->setBack(lastPtr);
            //last ptr 
            lastPtr->setNext(newNode);
            lastPtr = newNode;
            //move the current pointer
            curNode = curNode->getNext();
        } 
    }
}

template<typename ItemType>
void DoublyLinkedList<ItemType>::destroyList(){
    Node<ItemType>* curPtr;
    while(this->firstPtr!=nullptr){
        curPtr = this->firstPtr;
        this->firstPtr = this->firstPtr->getNext();
        delete curPtr;
    }
    this->lastPtr = nullptr;
    this->count = 0;
}

template<typename ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType>& otherList){
    this->firstPtr = nullptr;
    this->copyList(otherList);
}

template<typename ItemType>
const DoublyLinkedList<ItemType>& DoublyLinkedList<ItemType>::operator= (const DoublyLinkedList<ItemType>& otherList){
    //avoid self-copy
    if (this != &otherList){
        this->copyList(otherList);
    }
    return *this;
}