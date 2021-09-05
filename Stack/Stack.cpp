#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_STACK = 999;

template<class ItemType>
class StackInterface{
    public:
        /**Check whether this stack is empty
           @return True if the stakc is empty, false if not*/
        virtual bool isEmpty() const = 0;
        /**Adds a new entry to the top of this stack
           @post If the operation was successful, newEntry is at the top of the stack.
           @param newEntry: The object to be added as a newEntry
           @return True if the addition if successful or false if it's not. 
         */
        virtual bool push(const ItemType& newEntry) = 0;
        /**Removes the top of this stack
         * @post If the operation was successful, the top of the stack has been removed.
         * @return True if the removal is successful or false if not.
         */
        virtual bool pop() = 0;
        /**Returns the top of this stack
         * @pre: The stack is not empty
         * @post: The top of the stack has been returned, and the stack is unchanged
         * @return: The top of the stack
         */
        virtual ItemType peek() const = 0;
};

template<typename ItemType>
class ArrayStack:public StackInterface<ItemType>{
    private:
        ItemType items[MAX_STACK];
        int top;
    public:
        ArrayStack();
        bool isEmpty() const;
        bool push(const ItemType& newEntry);
        bool pop();
        ItemType peek() const;
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
class LinkedStack:public StackInterface<ItemType>{
    private:
        Node<ItemType>* topPtr;
    public:
        LinkedStack();
        LinkedStack(const LinkedStack<ItemType>& aStack);
        virtual ~LinkedStack();
        bool isEmpty() const;
        bool push(const ItemType& newItem);
        bool pop();
        ItemType peek() const;
};

int main(){
    StackInterface<int>* as = new ArrayStack<int>();
    as->push(4);
    as->push(10);
    as->pop();
    try{
        cout << as->peek() << endl;
        as->pop();
        cout << as->peek() << endl;
    }
    catch (logic_error e){
        cout << e.what() << endl;
    }


    LinkedStack<int> ls;
    ls.push(4);
    ls.push(11);
    LinkedStack<int> lsCopy(ls);
    lsCopy.pop();
    cout << lsCopy.peek() << endl;
    cout << ls.peek() << endl;
    return 0;
}

template<typename ItemType>
ArrayStack<ItemType>::ArrayStack():top(-1){}

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const{
    return (top < 0);
}

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry){
    bool result = false;
    if (this->top < MAX_STACK-1){
        top++;
        this->items[top] = newEntry; //may need operation overloading
        result = true;
    }
    return result;
}

template<typename ItemType>
bool ArrayStack<ItemType>::pop(){
    bool result = false;
    if (!this->isEmpty()){
        top--; //no need to delete
        result = true;
    }
    return result;
}

template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const{
    if(!this->isEmpty()){
        return items[top];
    }
    else{
        throw logic_error("This stack is empty!");
    }
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

template<typename ItemType>
LinkedStack<ItemType>::LinkedStack():topPtr(nullptr){}

template<typename ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack){
    //origChainPtr: always move on the old chain
    Node<ItemType>* origChainPtr = aStack.topPtr;
    //original stack is empty
    if (origChainPtr == nullptr){
        this->topPtr = nullptr;
    }
    else{
        //topPtr: always point to the head, won't move
        topPtr = new Node<ItemType>();
        topPtr->setItem(origChainPtr->getItem());
        
        //newChainPtr: always move on the new chain
        Node<ItemType>* newChainPtr = topPtr;
        while(origChainPtr->getNext() != nullptr){
            origChainPtr = origChainPtr->getNext();
            ItemType nextItem = origChainPtr->getItem();
            //newNodePtr: temporal pointer
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
        }
        //mark the bottom of the stack
        newChainPtr->setNext(nullptr);
    }
}

template<typename ItemType>
LinkedStack<ItemType>::~LinkedStack(){
    //pop until stack is empty
    while(!isEmpty()){
        pop();
    }
}

template<typename ItemType>
bool LinkedStack<ItemType>::isEmpty() const{
    return (topPtr == nullptr);
}

template<typename ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem){
    Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
    topPtr = newNodePtr;
    return true;
}

template<typename ItemType>
bool LinkedStack<ItemType>::pop(){
    bool result = false;
    if(!isEmpty()){
        Node<ItemType>* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();
        delete nodeToDeletePtr;
        result = true;
    }
    return result;
}

template<typename ItemType>
ItemType LinkedStack<ItemType>::peek() const{
    if(!this->isEmpty()){
        return topPtr->getItem();
    }
    else{
        throw logic_error("Empty stack!");
    }
}

