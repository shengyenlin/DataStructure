#include <iostream>
#include <cassert>

using namespace std;

template<typename ItemType>
class QueueInterface{
    public:
        /*Function to determine whether the queue is empty.
        @post: Returns true if the queue is empty, otherwise returns false.
        */
        virtual bool isEmptyQueue() const = 0;
        /*Function to determine whether the queue is full.
        @post: Returns true if the queue is full, otherwise returns false.
        */
        virtual bool isFullQueue() const = 0;
        /*Function to initialize the queue to an empty state.
        @post: The queue is empty.
        */
        virtual void initializeQueue() = 0;
        /*Function to return the first element of the queue.
        @pre: The queue exist and is not empty.
        @post: If the queue is empty, the program terminates, otherwise,
               the first element of the queue is returned.
        */
        virtual ItemType getFront() const = 0;  
        /*Function to return the last element of the queue.
        @pre: The queue exist and is not empty.
        @post: If the queue is empty, the program terminates, otherwise,
               the last element of the queue is returned.
        */
        virtual ItemType getBack() const = 0;
        /*Function to add queueElement to the queue.
        @pre: The queue exists and is not full.
        @post: The queue is changed and queueElement is added to the queue.
        */
        virtual void addToLast(const ItemType& queueElement) = 0;
        /*Function to remove the first element of the queue.
        @pre: The queue exists an is not empty.
        @post: The queue is changed and the first element is removed from the queue.
        */
        virtual void deleteFromFirst() = 0;
};

template <typename ItemType>
class QueueArray:public QueueInterface<ItemType>
{   
    private:
        int maxQueueSize; //variable to store the maximum queue size
        int count; //variable to store the number of elements in the queue.
        int queueFront; //variable to point to the first element of the queue
        int queueRear; //variable to point to the last element of the queue.
        ItemType* list; //pointer to the array that holds the queue elements
    public:
        //Constuctor
        QueueArray<ItemType>(int queueSize = 100);
        //Copy constructor
        QueueArray(const QueueArray<ItemType>& otherQueue);
        //Destructor
        ~QueueArray();
        /*Function to copy another queue.
        */
        void copyQueue(const QueueArray<ItemType>& otherQueue);
        /*Overload to assignment operator
        */
        const QueueArray<ItemType>& operator=(const QueueArray<ItemType>& otherQueue);
        /*Function to determine whether the queue is empty.
        @post: Returns true if the queue is empty, otherwise returns false.
        */
        bool isEmptyQueue() const;
        /*Function to determine whether the queue is full.
        @post: Returns true if the queue is full, otherwise returns false.
        */
        bool isFullQueue() const;
        /*Function to initialize the queue to an empty space.
        @post: The queue is empty.
        */
        void initializeQueue();
        /*Function to return the first element of the queue.
        @pre: The queue exists and is not empty.
        @post: If the queue is empty, the program terminates; otherwise, the first element of the queue is returned.
        */
        ItemType getFront() const;
        /*Function to return the last element of the queue.
        @pre: The queue exists and is not empty.
        @post: If the queue is empty, the program terminates; otherwise, the first element of the queue is returned.
        */
        ItemType getBack() const;
        /*Function to add queueElement to the queue.
        @pre: The queue exists and is not full.
        @post: The queue is changed and queueElement is added to the queue.
        */
        void addToLast(const ItemType& queueElement);
        /*Function to remove the first element of the queue.
        @pre: The queue exists an is not empty.
        @post: The queue is changed and the first element is removed from the queue.
        */
        void deleteFromFirst();
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
class LinkedQueue:public QueueInterface<ItemType>{
    private:
        Node<ItemType>* queueFront;
        Node<ItemType>* queueRear;
    public:
        //Deafult constructor
        LinkedQueue();
        //Copy constructor
        LinkedQueue(const LinkedQueue<ItemType>& otherQueue);
        //Destructor
        ~LinkedQueue();
        /*Overload the Assignment operator
        */
        const LinkedQueue<ItemType>& operator= (const LinkedQueue<ItemType>& otherQueue);
        /*Function to determine whether the queue is empty.
        @post: Returns true if the queue is empty, otherwise returns false.
        */
        bool isEmptyQueue() const;
        /*Function to determine whether the queue is full.
        @post: Returns true if the queue is full, otherwise returns false.
        */
        bool isFullQueue() const;
        /*Function to initialize the queue to an empty space.
        @post: The queue is empty.
        */
        void initializeQueue();
        /*Function to return the first element of the queue.
        @pre: The queue exists and is not empty.
        @post: If the queue is empty, the program terminates; otherwise, the first element of the queue is returned.
        */
        ItemType getFront() const;
        /*Function to return the last element of the queue.
        @pre: The queue exists and is not empty.
        @post: If the queue is empty, the program terminates; otherwise, the first element of the queue is returned.
        */
        ItemType getBack() const;
        /*Function to add queueElement to the queue.
        @pre: The queue exists and is not full.
        @post: The queue is changed and queueElement is added to the queue.
        */
        void addToLast(const ItemType& queueElement);
        /*Function to remove the first element of the queue.
        @pre: The queue exists an is not empty.
        @post: The queue is changed and the first element is removed from the queue.
        */
        void deleteFromFirst();
};

int main(){
    // QueueArray<int> QA(20);
    // QA.addToLast(10);
    // QA.addToLast(30);
    // QA.addToLast(50);
    // QA.addToLast(70);
    // QA.addToLast(90);
    // cout << QA.getBack() << endl;
    // cout << QA.getFront() << endl;

    // QueueArray<int> QA2 = QA;
    // QA.deleteFromFirst();
    // cout << "======================" << endl;
    // cout << QA.getBack() << endl;
    // cout << QA.getFront() << endl;
    // cout << "======================" << endl;
    // cout << QA2.getBack() << endl;
    // cout << QA2.getFront() << endl;

    LinkedQueue<int> LQ;
    LQ.addToLast(10);
    LQ.addToLast(30);
    LQ.addToLast(50);
    LQ.addToLast(70);
    LQ.addToLast(90);

    cout << LQ.getFront() << endl;
    cout << LQ.getBack() << endl;

    LinkedQueue<int> LQ2 = LQ;
    cout << LQ2.getFront() << endl;
    cout << LQ2.getBack() << endl;
    LQ.deleteFromFirst();
    cout << "======================" << endl;
    cout << LQ.getBack() << endl;
    cout << LQ.getFront() << endl;
    cout << LQ.isEmptyQueue() << endl;
    cout << "======================" << endl;
    cout << LQ2.getBack() << endl;
    cout << LQ2.getFront() << endl;
    cout << "======================" << endl;
    LQ2.deleteFromFirst(); // 30 50 70 90
    LQ2.deleteFromFirst(); // 50 70 90
    LQ2.deleteFromFirst(); // 70 90
    LQ2.deleteFromFirst(); // 90
    LQ2.deleteFromFirst(); // (Empty queue)
    LQ2.deleteFromFirst(); // Cannot remove from an empty queue.
    cout << LQ2.getFront() << endl; //assertion fail
    return 0;
}

template<typename ItemType>
bool QueueArray<ItemType>::isEmptyQueue() const{
    return (count == 0);
}

template<typename ItemType>
bool QueueArray<ItemType>::isFullQueue() const{
    return (count == maxQueueSize);
}

template<typename ItemType>
void QueueArray<ItemType>::initializeQueue(){
    queueFront = 0;
    queueRear = maxQueueSize - 1;
    count = 0;
}

template<typename ItemType>
ItemType QueueArray<ItemType>::getFront() const{
    assert(!isEmptyQueue());
    return list[queueFront];
}

template<typename ItemType>
ItemType QueueArray<ItemType>::getBack() const{
    assert(!isEmptyQueue());
    return list[queueRear];
}

template<typename ItemType>
void QueueArray<ItemType>::addToLast(const ItemType& queueElement){
    if (!isFullQueue()){
        //use the mod operator to advance queueRear
        //because we assumes the array is circular
        queueRear = (queueRear + 1) % maxQueueSize;
        count++;
        list[queueRear] = queueElement;
    }
    else{
        cout << "Cannot add to  a full queue." << endl;
    }
}

template<typename ItemType>
void QueueArray<ItemType>::deleteFromFirst(){
    if (!isEmptyQueue()){
        count--;
        //use the mod operator to advance queueRear
        //because we assumes the array is circular
        queueFront = (queueFront + 1) % maxQueueSize;
    }
    else{
        cout << "Cannot remove from an empty queue." << endl;
    }
}

template<typename ItemType>
QueueArray<ItemType>::QueueArray(int queueSize){
    if (queueSize <= 0){
        cout << "Size of the array to hold the queue must be positive." << endl;
        cout << "Creating an array of size 100";
        maxQueueSize = 100;
    }
    else{
        maxQueueSize = queueSize;
    }
    initializeQueue();
    list = new ItemType[maxQueueSize];
}

template<typename ItemType>
QueueArray<ItemType>::~QueueArray(){
    delete [] list;
}

template<typename ItemType>
void QueueArray<ItemType>::copyQueue(const QueueArray<ItemType>& otherQueue){
    this->maxQueueSize = otherQueue.maxQueueSize;
    this->count = otherQueue.count;
    this->queueFront = otherQueue.queueFront;
    this->queueRear = otherQueue.queueRear;
    this->list = new ItemType[maxQueueSize];
    for (int i = 0; i < count; i++){
        this->list[this->queueFront+i] = otherQueue.list[otherQueue.queueFront+i];
    }
}

template<typename ItemType>
QueueArray<ItemType>::QueueArray(const QueueArray<ItemType>& otherQueue){
    this->copyQueue(otherQueue);
}

template<typename ItemType>
const QueueArray<ItemType>& QueueArray<ItemType>::operator=(const QueueArray<ItemType>& otherQueue){
    if (this != &otherQueue){
        this->copyQueue(otherQueue);
    }
    return *this;
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
bool LinkedQueue<ItemType>::isEmptyQueue() const{
    return (queueFront == nullptr);
}

template<typename ItemType>
bool LinkedQueue<ItemType>::isFullQueue() const{
    return false;
}

template<typename ItemType>
void LinkedQueue<ItemType>::initializeQueue(){
    //we need to make sure that the queue is empty when being initialized
    Node<ItemType>* temp;
    while(queueFront != nullptr){
        temp = queueFront;
        queueFront = queueFront->getNext();
        delete temp;
    }
    queueRear = nullptr;
}

template<typename ItemType>
void LinkedQueue<ItemType>::addToLast(const ItemType& queueElement){
    //Create new node
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->setItem(queueElement);
    newNode->setNext(nullptr);

    //If the queue is empty
    if (this->isEmptyQueue()){
        queueFront = newNode;
        queueRear = newNode;
    }
    else{
        queueRear->setNext(newNode);
        queueRear = queueRear->getNext();
    }
}

template<typename ItemType>
ItemType LinkedQueue<ItemType>::getFront() const{
    assert(!this->isEmptyQueue());
    return (queueFront->getItem());
}

template<typename ItemType>
ItemType LinkedQueue<ItemType>::getBack() const{
    assert(!this->isEmptyQueue());
    return (queueRear->getItem());
}

template<typename ItemType>
void LinkedQueue<ItemType>::deleteFromFirst(){
    Node<ItemType>* temp;
    if(!this->isEmptyQueue()){
        //cout << this->isEmptyQueue() << endl;
        temp = queueFront;
        queueFront = queueFront->getNext();
        delete temp;
        //If there's only one element in the queue
        if (queueFront == nullptr){
            queueRear = nullptr;
        }
    }
    else{
        cout << "Cannot remove from an empty queue." << endl;
    }
}

template<typename ItemType>
LinkedQueue<ItemType>::LinkedQueue(){
    queueFront = nullptr;
    queueRear = nullptr;
}

template<typename ItemType>
LinkedQueue<ItemType>::~LinkedQueue(){
    Node<ItemType>* temp;
    while(queueFront != nullptr){
        temp = queueFront;
        queueFront = queueFront->getNext();
        delete temp;
    }
    queueRear = nullptr;
}

template<typename ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& otherQueue){
    if (otherQueue.isEmptyQueue()){
        this->queueFront = nullptr;
        this->queueRear = nullptr;
    }
    else{
        //traverse the list with curPtrOtehr on otherQueue
        Node<ItemType>* curPtrOther = otherQueue.queueFront;
        this->queueFront = new Node<ItemType>;
        this->queueFront->setItem(curPtrOther->getItem());
        Node<ItemType>* curPtrThis = queueFront;
        curPtrOther = curPtrOther->getNext();
        while(curPtrOther != nullptr){
            //create new node
            Node<ItemType>* tempNode = new Node<ItemType>;
            //update information
            tempNode->setItem(curPtrOther->getItem());
            //set the next node of curPtrthis to this new node
            curPtrThis->setNext(tempNode);
            //advance pointer
            curPtrOther = curPtrOther->getNext();
            curPtrThis = curPtrThis->getNext();
        }
        this->queueRear = curPtrThis;
    }
}

template<typename ItemType>
const LinkedQueue<ItemType>& LinkedQueue<ItemType>::operator=(const LinkedQueue<ItemType>& otherQueue){
    if (this != &otherQueue){
        LinkedQueue<ItemType> LQ(otherQueue);
        return LQ;
    }
    else{
        return *this;
    }
}