#include <iostream>
#include <cassert>

using namespace std;

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

template <typename ItemType>
class LinkedListIterator{
    private:
        //pointer point to the cuurent node in the linked list
        Node<ItemType>* current;
    public:
        /*Default Constructor
        @post: current = nullptr
        */
        LinkedListIterator();
        /*Constructor with a parameter
        @post: current = ptr
        */
        LinkedListIterator(Node<ItemType>* ptr);
        /*Function to overload the deferencing operator *.
        @post: returnst the info contained in the node.
        */
        ItemType operator* ();
        /*Overload the pre-incerment operator 
        @post: the iterator is advanced to the next node
        */
        LinkedListIterator<ItemType> operator++ ();
        /*Overload the equality operator
        @post: returns true if this iterator is equal to the
               iterator specified by the right
               otherwise, return false
        */
        bool operator== (const LinkedListIterator<ItemType>& Iterator) const;
        /*Overload the not equal operator
        @post: returns true if this iterator is not equal to the
               iterator specified by the right
               otherwise, return false
        */
        bool operator!= (const LinkedListIterator<ItemType>& Iterator) const;
};

template<typename ItemType>
class LinkedListInterface{
    private:
        /*Function to make a copy of otherList
        @post: A copy of otherList is created and assigned to the list
        */
        void copyList(const LinkedListInterface<ItemType>& otherList);
    protected:
        //variable to store the number of list elements
        int count;
        //pointer to the first node of the list
        Node<ItemType>* firstPtr;
        //pointer to the last node of the list
        Node<ItemType>* lastPtr;
    public:
        /*default constructor
        initialize the list to an empty state.
        @post: first = nullptr, last = nullptr, count = 0
        */
        LinkedListInterface();
        /*copy constructor
        */
        LinkedListInterface(const LinkedListInterface<ItemType>& otherList);
        /*destructor
        Deletes all the nodes from the list.
        @post:the list object is destroyed
        */
        ~LinkedListInterface();
        /*Overload the assignment operator.
        */
        const LinkedListInterface<ItemType>& operator= (const LinkedListInterface<ItemType>&);
        /*Initialize the list to an empty state.
        @post: first = fullptr, last = nullptr, count = 0
        */
        void initializeList();
        /*Function to determine whether the list is empty
        @post: returns true if the list is empty, otherwise false
        */
        bool isEmpty() const;
        /*Function to output the data contained in the linked list
        */
        void print() const;
        /*Function to return the number of nodes in the list
        */
        int getLength() const;
        /*Function to delete all the nodes from the list
        @post: first = nullptr, last = nullptr, count = 0
        */
        void destroyList();
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
        virtual bool search(const ItemType& searchItem) const = 0;
        /*Function to insert nweItem at the beginning of the list
        @post:first points to the new list, newItem is inserted at the beginning of the list
              last points to the last node in the list
              count is incremented by 1
        */
        virtual void insertFirst(const ItemType& newItem) = 0;
        /*Function to insert nweItem at the end of the list
        @post:first points to the new list, newItem is inserted at the beginning of the list
              last points to the last node in the list
              count is incremented by 1
        */
        virtual void insertLast(const ItemType& newItem) = 0;
        /*Function to delete item from the list
        @post: If found, the node containing deleteItem is deleted from the list
        first points to the first node
        last points to the last node
        count is decremented by 1
        */
        virtual void deleteNode(const ItemType& deleteItem) = 0;
        /*Function to return an iterator at the beginning of the linked list
        @post: returns an iterator such that current is set to first
        */
        LinkedListIterator<ItemType> getFrontItr();
        /*Function to return an iterator at the end of the linked list
        @post: returns an iterator such that current is set to nullptr
        */
        LinkedListIterator<ItemType> getEndItr();
};

template<typename ItemType>
class UnorderedLinkedList:public LinkedListInterface<ItemType>{
    public:
        /*Function to determine whether searchItem is in the list
        @post: returns true if searchItem is in the list, otherwise false
        */
        bool search(const ItemType& searchItem) const;
        /*Function to insert newItem at the beginning of the list.
        @post: first pointer points to the new list, newItem is inserted
        at the beginning of the list, last pointer to the last node,
        and count is incremented by 1.
        */
        void insertFirst(const ItemType& newItem);
        /*Function to insert newItem at the last of the list
        @post: first pointer points to the new list, newItem is inserted
        at the beginning of the list, last pointer to the last node,
        and count is incremented by 1.
        */
        void insertLast(const ItemType& newItem);    
        /*Function to delete deleteItem from the list
        @post: If found, the node containing deleteItem is deleted from
        the list.
        First pointer points to the first node, last pointer points to
        the last node of the updated list, and count is decremented by 1
        */
        void deleteNode(const ItemType& deleteItem);
};

template<typename ItemType>
class OrderedLinkedList:public LinkedListInterface<ItemType>{
    public:
        /*Function to determine whether searchItem is in the list
        @post: returns true if searchItem is in the list, otherwise false
        */
        bool search(const ItemType& searchItem) const;
        /*Function to insert newItem in the list/
        @post: first pointer point to the new list, newItem is inserted at
        the proper place in the list, count is incremented by 1.
        */
        void insert(const ItemType& newItem);
        /*Function to insert newItem at the beginning of the list.
        @post: first pointer points to the new list, newItem is inserted
        at the beginning of the list, last pointer to the last node,
        and count is incremented by 1.
        */
        void insertFirst(const ItemType& newItem);
        /*Function to insert newItem at the last of the list
        @post: first pointer points to the new list, newItem is inserted
        at the beginning of the list, last pointer to the last node,
        and count is incremented by 1.
        */
        void insertLast(const ItemType& newItem);    
        /*Function to delete deleteItem from the list
        @post: If found, the node containing deleteItem is deleted from
        the list.
        First pointer points to the first node, last pointer points to
        the last node of the updated list, and count is decremented by 1
        */
        void deleteNode(const ItemType& deleteItem);
};

int main(){
    UnorderedLinkedList<int> ULL;
    ULL.insertFirst(15);
    ULL.print();
    ULL.insertLast(20);
    ULL.print();
    ULL.insertLast(30);
    ULL.insertFirst(105);
    ULL.print();
    cout << ULL.getLength() << endl;
    if (ULL.search(30)){
        cout << "Searched!!" << endl;
    }
    else{
        cout << "not searched!!" << endl;
    }

    if (ULL.search(5)){
        cout << "Searched!!" << endl;
    }
    else{
        cout << "not searched!!" << endl;
    }
    ULL.deleteNode(105);
    cout << ULL.getLength() << endl;
    ULL.print();
    ULL.deleteNode(20);
    cout << ULL.getLength() << endl;
    ULL.print();
    ULL.deleteNode(30);
    cout << ULL.getLength() << endl;
    ULL.print();
    cout << ULL.getFront() << endl;

    OrderedLinkedList<int> OLL1;
    int num = 0;
    cout << "Enter number ending with -999" << endl;
    cin >> num;
    while (num != -999){
        OLL1.insert(num);
        cin >> num;
    }
    OLL1.print();
    OrderedLinkedList<int> OLL2(OLL1);
    OLL2.print();
    OLL2.deleteNode(10);
    cout << "Remaining nodes in list1: ";
    OLL1.print();
    cout << "Remaining nodes in list2: ";
    OLL2.print();
    return 0;
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
}

template <typename ItemType>
LinkedListIterator<ItemType>::LinkedListIterator():current(nullptr){}

template <typename ItemType>
LinkedListIterator<ItemType>::LinkedListIterator(Node<ItemType>* ptr)
    :current(ptr){}

template <typename ItemType>
ItemType LinkedListIterator<ItemType>::operator*(){
    return (this->current->getItem());
}  

template <typename ItemType>
LinkedListIterator<ItemType> LinkedListIterator<ItemType>::operator++(){
    current = current->getNext();
    return *this;
}  

template <typename ItemType>
bool LinkedListIterator<ItemType>::operator== (const LinkedListIterator<ItemType>& Iterator) const{
    return (this->current == Iterator.current);
}

template <typename ItemType>
bool LinkedListIterator<ItemType>::operator!= (const LinkedListIterator<ItemType>& Iterator) const{
    return (this->current != Iterator.current);
}

template<typename ItemType>
LinkedListInterface<ItemType>::LinkedListInterface()
    :firstPtr(nullptr), lastPtr(nullptr), count(0){}


template<typename ItemType>
void LinkedListInterface<ItemType>::destroyList(){
    Node<ItemType>* tempPtr;
    while(this->firstPtr != nullptr){
        tempPtr = this->firstPtr;
        this->firstPtr = this->firstPtr->getNext();
        delete tempPtr;
    }
    this->lastPtr = nullptr;
    this->count = 0;
}

template<typename ItemType>
void LinkedListInterface<ItemType>::initializeList(){
    //if the list has any nodes, delete them
    this->destroyList();
}

template<typename ItemType>
void LinkedListInterface<ItemType>::print() const{
    Node<ItemType>* curPtr = this->firstPtr;
    while (curPtr != nullptr){
        cout << curPtr->getItem() << " ";
        curPtr = curPtr->getNext();
    }
    cout << endl;
}

template<typename ItemType>
int LinkedListInterface<ItemType>::getLength() const{
    return count;
}

template<typename ItemType>
ItemType LinkedListInterface<ItemType>::getFront() const{
    //if the list is empty, the assert statement terminates the program
    assert(this->firstPtr != nullptr);
    return (this->firstPtr->getItem());
}

template<typename ItemType>
ItemType LinkedListInterface<ItemType>::getBack() const{
    //if the list is empty, the assert statement terminates the program
    assert(this->lastPtr != nullptr);
    return (this->lastPtr->getItem());
}

template<typename ItemType>
LinkedListInterface<ItemType>::~LinkedListInterface(){
    this->destroyList();
}

template<typename ItemType>
void LinkedListInterface<ItemType>::copyList(const LinkedListInterface<ItemType>& otherList){
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
        lastPtr = firstPtr;  //make last ptr to the first node
        curNode = curNode->getNext();

        //copy the remaining list
        while(curNode != nullptr){
            //create and copy information
            newNode = new Node<ItemType>;
            newNode->setItem(curNode->getItem());
            newNode->setNext(nullptr);
            //last ptr 
            lastPtr->setNext(newNode);
            lastPtr = newNode;
            //move the current pointer
            curNode = curNode->getNext();
        } 
    }
}

template<typename ItemType>
LinkedListInterface<ItemType>::LinkedListInterface(const LinkedListInterface<ItemType>& otherList){
    this->firstPtr = nullptr;
    this->copyList(otherList);
}

template<typename ItemType>
const LinkedListInterface<ItemType>& LinkedListInterface<ItemType>::operator=(const LinkedListInterface<ItemType>& otherList){
    //avoid self-copy
    if (this != &otherList){
        copyList(otherList);
    }
    return *this;
}


template<typename ItemType>
LinkedListIterator<ItemType> LinkedListInterface<ItemType>::getFrontItr(){
    LinkedListIterator<ItemType> temp(this->firstPtr);
    return temp;
}

template<typename ItemType>
LinkedListIterator<ItemType> LinkedListInterface<ItemType>::getEndItr(){
    LinkedListIterator<ItemType> temp(nullptr);
    return temp;
}

template<typename ItemType>
bool UnorderedLinkedList<ItemType>::search(const ItemType& searchItem) const{
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    bool found = false;
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
void UnorderedLinkedList<ItemType>::insertFirst(const ItemType& newItem){
    //pointer to create the new node
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->setItem(newItem);
    newNode->setNext(this->firstPtr);
    this->firstPtr = newNode;
    this->count++;
    //if the list is empty, newNode is also the last node in the list
    if (this->lastPtr==nullptr){
        this->lastPtr = newNode;
    }
}

template<typename ItemType>
void UnorderedLinkedList<ItemType>::insertLast(const ItemType& newItem){
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->setItem(newItem);
    newNode->setNext(nullptr);
    //if the list is empty
    //newNoder is both the first and the last node 
    if (this->firstPtr == nullptr){
        this->firstPtr = newNode;
        this->lastPtr = newNode;
        this->count++;
    }
    else{
        this->lastPtr->setNext(newNode);
        this->lastPtr = newNode;
        this->count++;
    }
}

template<typename ItemType>
void UnorderedLinkedList<ItemType>::deleteNode(const ItemType& deleteItem){
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    //pointer just before curPtr
    Node<ItemType>* trailCurPtr;
    bool found;
    //case1: the list is empty
    if (this->firstPtr == nullptr){
        cout << "Cannot delete from and empty list" << endl;
    }

    else{
        //case2 : the list is not empty and the node to be deleted
        //is the first node
        if (this->firstPtr->getItem() == deleteItem){
            curPtr = this->firstPtr;
            this->firstPtr = this->firstPtr->getNext();
            this->count--;
            //the list has only one node
            if (this->firstPtr == nullptr){
                this->lastPtr == nullptr;
            }
            delete curPtr;
        }
        //search the list with the given info
        else{
            found = false;
            trailCurPtr = this->firstPtr;
            curPtr = this->firstPtr->getNext();
            while(curPtr!=nullptr && !found){
                if (curPtr->getItem() != deleteItem){
                    trailCurPtr = curPtr;
                    curPtr = curPtr->getNext();
                }
                else{
                    found = true;
                }
            }
            //case3: if found, delete the node
            if (found){
                //case3a: the found node is not the last node
                trailCurPtr->setNext(curPtr->getNext());
                this->count--;
                //case3b: the found node is the last node
                if(curPtr == this->lastPtr){
                    this->lastPtr = trailCurPtr;
                }
            }
            else{
                //case4: the node is not found
                cout << "The item to be deleted is not in the list" << endl;
            }

        }
    }
}

template<typename ItemType>
bool OrderedLinkedList<ItemType>::search(const ItemType& searchItem) const{
    bool found = false;
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    curPtr = this->firstPtr;
    while(curPtr != nullptr && !found){
        if (curPtr->getItem() == searchItem){
            found = true;
            break;
        }
        //if the current value is greater than the searchItem
        //it's impossible to find searchItem afterwards
        else if (curPtr->getItem() > searchItem){
            found = false;
            break;
        }
        else{
            curPtr = curPtr->getNext();
        }
    }
    return found;
}

template<typename ItemType>
void OrderedLinkedList<ItemType>::insert(const ItemType& newItem){
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    //pointer just before curPtr
    Node<ItemType>* trailCurPtr;
    //pointer to create a node
    Node<ItemType>* newNode;
    bool found;

    newNode = new Node<ItemType>;
    newNode->setItem(newItem);
    newNode->setNext(nullptr);

    //case1: the list is empty
    if (this->firstPtr == nullptr){
        this->firstPtr = newNode;
        this->lastPtr = newNode;
        this->count++;
    }
    else{
        curPtr = this->firstPtr;
        found = false;
        //search the position for the newItem in the list
        while(curPtr != nullptr && !found){
            //stop and record the position
            if(curPtr->getItem() >= newItem){
                found = true;
            }
            else{
                trailCurPtr = curPtr;
                curPtr = curPtr->getNext();
            }
        }
        //case2: newItem is smaller than the smallest thing in the linked list
        if (curPtr == this->firstPtr){
            newNode->setNext(this->firstPtr);
            this->firstPtr = newNode;
            this->count++;
        }
        //case3: insert somewhere not the beginning
        else{
            trailCurPtr->setNext(newNode);
            newNode->setNext(curPtr);
            //case3b: newItem is larger than the largest thing in the linked list
            if (curPtr==nullptr){
                this->lastPtr = newNode;
            }
            this->count++;
        }
    }
}

template<typename ItemType>
void OrderedLinkedList<ItemType>::insertFirst(const ItemType& newItem){
    this->insert(newItem);
}

template<typename ItemType>
void OrderedLinkedList<ItemType>::insertLast(const ItemType& newItem){
    this->insert(newItem);
}

template<typename ItemType>
void OrderedLinkedList<ItemType>::deleteNode(const ItemType& deleteItem){
    //pointer to traverse the list
    Node<ItemType>* curPtr;
    //pointer just before CurPtr;
    Node<ItemType>* trailCurPtr;
    bool found;
    //case1 : the list is empty
    if (this->firstPtr == nullptr){
        cout << "Cannot delete from an empty list" << endl;
    }
    else{
        curPtr = this->firstPtr;
        found = false;
        //traverse the list
        while(curPtr != nullptr && !found){
            if(curPtr->getItem() >= deleteItem){
                found = true;
            }
            else{
                trailCurPtr = curPtr;
                curPtr = curPtr->getNext();
            }
        }
        //case4: the deleted item is not found
        if (curPtr == nullptr){
            cout << "The item to be deleted is not in the list" << endl;
        }
        else{
            if (curPtr->getItem() == deleteItem){
                if (this->firstPtr == curPtr){
                    //case2: the deleted item is the first node
                    this->firstPtr = this->firstPtr->getNext();
                    if (this->firstPtr == nullptr){
                        this->lastPtr = nullptr;
                    }
                    delete curPtr;
                }
                else{
                    trailCurPtr->setNext(curPtr->getNext());
                    //case3b: the deleted item is the last node
                    if (curPtr == this->lastPtr){
                        this->lastPtr = trailCurPtr;
                    }
                }
                this->count--;
            }
            else{
                cout << "The item to be deleted is not in the list" << endl;
            }
        }
    }
}