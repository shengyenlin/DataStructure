#include <iostream>
#include <string>
#include <queue>

using namespace std;

class CustomerType{
    private:
        int customerNumber;
        int arrivalTime;
        int waitingTime;
        int transactionTime;
    public:
        /*Constructor to initialize the instance variables according to the parameters
        If no value is specified in the object declaration, the default values are assigned.
        @post: customerNumber = cN, arrivalTime = arriveTime, waitingTime = waitTime, transactionTime = transTime
        */
        CustomerType(int cN = 0, int arriveTime = 0, int waitTime = 0, int transTime = 0);
        /*Function to initialize the instance variables according to the parameters
        @post: customerNumber = cN, arrivalTime = arriveTime, waitingTime = waitTime, transactionTime = transTime
        */
        void setCustomerInfo(int cN = 0, int arriveTime = 0, int waitTime = 0, int transTime = 0);
        /*Function to return the waiting time.
        @post: The value of waitingTime is returned.
        */
        int getWaitingTime() const;
        /*Function to set the waiting time of a customer.
        @post: waitingTime = time;
        */
        void setWaitingTime(int time);
        /*Function to set the waiting time of a customer.
        @post: waitingTime++;
        */
        void incrementWaitingTime();
        /*Function to return the arrival time.
        @post: The value of arrivalTime is returned.
        */       
        int getArrivalTime() const;
        /*Function to return the transaction time.
        @post: The value of transactionTime is returned.
        */       
        int getTransactionTime() const;
        /*Function to return the customer number.
        @post: The value of customerNumber is returned.
        */       
        int getCustomerNumber() const;
};

class ServerType{
    private:
        CustomerType currentCustomer;
        string status;
        int transactionTime;
    public:
        /*Default constructor
        Sets the value of the instance variable to their default values.
        @post: currentCustomer is initialized by its default constructor.
        status = "free", transaction time is initialized to 0.
        */
        ServerType();
        /*Function to determine whether if the server is free.
        */
        bool isFree() const;
        /*Function to set the status of the server to busy.
        */
        void setBusy();
        /*Function to set the status of the server to "free".
        */
        void setFree();
        /*Function to set the transaction time according to param t
        @post: transactionTime = t;
        */
        void setTransactionTime(int t);
        /*Function to set the transaction time according to the transaction time of the current customer.
        @post: transactionTime = currentCustomer.transactionTime;
        */
        void setTransactionTime();
        /*Function to return the remaining transaction time.
        @post: The value of transactionTime is returned.
        */
        int getRemainingTransactionTime() const;
        //Function to decrease the transactionTime by 1 unit.
        //@post: transactionTime--;
        void decreaseTransactionTime();
        //Function to set the info of the current customer
        //according to the parameter cCustomer.
        //@post: currentCustomer = cCustomer;
        void setCurrentCustomer(CustomerType cCustomer);
        //Function to return the customer number of the current
        //customer.
        //@post: The value of customerNumber of the
        // current customer is returned.
        int getCurrentCustomerNumber() const;
        //Function to return the arrival time of the current
        //customer.
        //@post: The value of arrivalTime of the current
        // customer is returned.
        int getCurrentCustomerArrivalTime() const;
        //Function to return the current waiting time of the
        //current customer.
        //@post: The value of transactionTime is returned.
        int getCurrentCustomerWaitingTime() const;
        //Function to return the transaction time of the
        //current customer.
        //@post: The value of transactionTime of the
        // current customer is returned.
        int getCurrentCustomerTransactionTime() const;
};

class ServerListType{
    private:
        int numOfServers;
        ServerType* servers;
    public:
        //Constructor to initialize a list of servers
        //Post-condition: numOfServers = num
        //       A list of servers, specified by num, is created and
        //       each server is initialized fo "free".
        ServerListType(int num = 1);      
        //Destructor
        //Post-condition: The list of servers si destroyed.
        ~ServerListType();
        //Function to search the list of servers.
        //Post-condition: If a free server is found, returns its ID
        //                Otherwise, returns -1.
        int getFreeServerID() const;
        //Function to return the number of busy servers.
        //Post-condition: The number of busy servers is returned.
        int getNumberOfBusyServers() const;
        //Function to set a server busy.
        //Post-condition: The server specified by serverID is set to "busy",
        //                to serve the customer specified by cCustomer,
        void setServerBusy(int serverID, CustomerType cCustomer, int tTime);
        //Function to set a server busy.
        //Post-condition: The server specified by serverID is set to "busy", 
        //                to serve the customer specified by cCustomer,
        //                and the transaction time it set according to the 
        //                parameter tTime.
        void setServerBusy(int serverID, CustomerType cCustomer);
        //Function to update the status of a server.
        //Post-condition: The transaction time of each busy server
        //is decremented by oneunit. If the transaction time of a busy
        //server is reduced to zero, the server is set to "free".
        //Moreover, if the actual parameter corresponding to outFile is cout,
        //a message indicating which customer has been serverd is printed on the
        //screen, together with the customer's departing time.
        //Otherwise, the output is sent to a file specified by the user.
        void updateServers(ostream& outFile);
};

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

class WaitingCustomerQueue:public QueueArray<CustomerType>{
    public:
        //Constuctor
        //Post-condition: The queue isinitialized according to
        //                the parameter size. The value of size
        //                is passed to the constructor of LinkedQueue
        WaitingCustomerQueue(int size = 100);
        //Function to increment time of each customer in the queue by one time unit
        void updateWaitingQueue();
};

void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival);
void runSimulation();

int main(){

    return 0;
}

void CustomerType::setCustomerInfo(int cN, int arriveTime, int waitTime, int transTime){
    customerNumber = cN;
    arrivalTime = arriveTime;
    waitingTime = waitTime;
    transactionTime = transTime;
}

CustomerType::CustomerType(int cN, int arriveTime, int waitTime, int transTime){
    setCustomerInfo(cN, arriveTime, waitTime, transTime);
}

int CustomerType::getWaitingTime() const{
    return waitingTime;
}

void CustomerType::setWaitingTime(int time){
    waitingTime = time;
}

void CustomerType::incrementWaitingTime(){
    waitingTime++;
}

int CustomerType::getArrivalTime() const{
    return arrivalTime;
}

int CustomerType::getTransactionTime() const{
    return transactionTime;
}

int CustomerType::getCustomerNumber() const{
    return customerNumber;
}

ServerType::ServerType(){
    status = "free";
    transactionTime = 0;
}

bool ServerType::isFree() const{
    return (status == "free");
}

void ServerType::setBusy(){
    status = "busy";
}

void ServerType::setFree(){
    status = "free";
}

void ServerType::setTransactionTime(int t){
    transactionTime = t;
}
void ServerType::setTransactionTime(){
    int time;
    time = currentCustomer.getTransactionTime();
    transactionTime = time;
}
void ServerType::decreaseTransactionTime(){
    transactionTime--;
}

int ServerType::getRemainingTransactionTime() const{
    return transactionTime;
}

void ServerType::setCurrentCustomer(CustomerType cCustomer){
    currentCustomer = cCustomer;
}

int ServerType::getCurrentCustomerNumber() const{
    return currentCustomer.getCustomerNumber();
}

int ServerType::getCurrentCustomerArrivalTime() const{
    return currentCustomer.getArrivalTime();
}

int ServerType::getCurrentCustomerWaitingTime() const{
    return currentCustomer.getWaitingTime();
}

int ServerType::getCurrentCustomerTransactionTime() const{
    return currentCustomer.getTransactionTime();
}

ServerListType::ServerListType(int num){
    numOfServers = num;
    servers = new ServerType[num];
}

ServerListType::~ServerListType(){
    delete [] servers;
}

int ServerListType::getFreeServerID() const{
    int serverID = -1;
    for (int i = 0; i < numOfServers; i++){
        if (servers[i].isFree()){
            serverID = i;
            break;
        }
    }
    return serverID;
}

int ServerListType::getNumberOfBusyServers() const{
    int busyServers = 0;
    for (int i = 0; i < numOfServers; i++){
        if (!servers[i].isFree()){
            busyServers++;
        }
    }
    return busyServers;
}

void ServerListType::setServerBusy(int serverID, CustomerType cCustomer, int tTime){
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(tTime);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void ServerListType::setServerBusy(int serverID, CustomerType cCustomer){
    int time = cCustomer.getTransactionTime();
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(time);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void ServerListType::updateServers(ostream& outFile){
    for (int i = 0; i < numOfServers; i++){
        if (!servers[i].isFree()){
            servers[i].decreaseTransactionTime();
            if (servers[i].getRemainingTransactionTime() == 0){
                outFile << "From server number " << (i+1)
                        << " customer number "
                        << servers[i].getCurrentCustomerNumber()
                        << "\n departed at clock unit "
                        << servers[i].getCurrentCustomerArrivalTime() 
                        + servers[i].getCurrentCustomerWaitingTime()
                        + servers[i].getCurrentCustomerTransactionTime()
                        << endl;
                servers[i].setFree(); 
            }
        }
    }
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

WaitingCustomerQueue::WaitingCustomerQueue(int size):
    QueueArray<CustomerType>(size){}

void WaitingCustomerQueue::updateWaitingQueue(){
    CustomerType cust;
    //create a dummy customer
    cust.setWaitingTime(-1);
    int wTime = 0;
    this->addToLast(cust);
    while(wTime != -1){
        cust = this->getFront();
        this->deleteFromFirst();

        wTime = cust.getWaitingTime();
        //we find the dummy customer
        //end the updating process
        if (wTime == -1){
            break;
        }
        //update waiting time
        cust.incrementWaitingTime();
        this->addToLast(cust);
    }
}

void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival){
    cout << "Enter the simulation time: ";
    cin >> sTime;
    cout << endl;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << endl;
    cout << "Enter the transaction time: ";
    cin >> transTime;
    cout << endl;
    cout << "Enter the time between customers arrival: ";
    cin >> tBetweenCArrival;
    cout << endl;
}

void runSimulation(){
    //to be finished :)
}