#include <iostream>
#include <stack>
using namespace std;

template<typename ItemType>
class TreeNode{
    private:
        ItemType val;
        TreeNode<ItemType>* leftLink;
        TreeNode<ItemType>* rightLink;
    public:
        ItemType getVal();
        TreeNode<ItemType>* getLeftLink() const;
        TreeNode<ItemType>* getRightLink() const;
        void setVal(ItemType val);
        void setLeftLink(TreeNode<ItemType>* leftNodePtr);
        void setRightLink(TreeNode<ItemType>* rightNodePtr);
        template <typename ItemType2> //???
        friend class BinarySearchTree;
        template <typename ItemType2> //???
        friend class BinaryTreeInterface;
};

template<typename ItemType>
class BinaryTreeInterface{
    private:
        //Make a copy of the binary tree to which otherTreeRoot points.
        //The pointer copiedTreeRoot points to the root of the copied binary tree.
        void copyTree(TreeNode<ItemType>* &copiedTreeRoot, TreeNode<ItemType>* otherTreeRoot);
        //Function to destroy the binary tree to which NodePtr points.
        //Post-condition: NodePtr == nullptr;
        void destroy(TreeNode<ItemType>* NodePtr);
        //Function to do an inorder traversal of the binary tree to which NodePtr points.
        void inorder(TreeNode<ItemType>* NodePtr) const;
        //Function to do an inorder traversal of the binary tree to which NodePtr points.
        //The parameter visit, which is a function, specifies the action
        //to be taken at each node.
        //(*visit): function pointer
        void inorder(TreeNode<ItemType>* NodePtr, int (*visit) (ItemType&));
        //Function to do an preorder traversal of the binary tree to which NodePtr points.
        void preorder(TreeNode<ItemType>* NodePtr) const;
        //Function to do an postorder traversal of the binary tree to which NodePtr points.
        void postorder(TreeNode<ItemType>* NodePtr) const;
        //Function to return the height of the binary tree to which NodePtr points.
        int getHeight(TreeNode<ItemType>* NodePtr) const;
        //Function to return the number of nodes in the binary tree to which NodePtr points.
        int getNodeCount(TreeNode<ItemType>* NodePtr) const;
        //Function to return the number of leaves in the binary tree to which NodePtr points.
        int getLeavesCount(TreeNode<ItemType>* NodePtr) const;
    protected:
        TreeNode<ItemType>* rootNodePtr;
    public:
        //copy constructor
        BinaryTreeInterface(const BinaryTreeInterface<ItemType>& otherBinaryTree);
        //default constructor
        BinaryTreeInterface();
        //destructor
        ~BinaryTreeInterface();
        //overload the assignment operator
        const BinaryTreeInterface<ItemType>& operator= (const BinaryTreeInterface<ItemType> &otherBinaryTree);
        //Function to determine whether the binary tree is empty
        //Post-condition: returns true if the binary tree is empty, else returns false.
        bool isEmpty() const;
        //Function to do an inorder traversal of the binary tree.
        void inorderTraversal() const;
        //Function to do an inorder treaversal of the binary tree.
        //The parameter visit, which is a function, specifies the action
        //to be taken at each node.
        void inorderTraversal(int (*visit) (ItemType&));
        //Function to do an inorder traversal of the binary tree in an interative way.
        void iterativeInorderTraversal() const;
        //Function to do a preorder traversal of the binary tree.
        void preorderTraversal() const;
        //Function to do a preorder traversal of the binary tree in an iterative way.
        void iterativePreorderTraversal() const;
        //Function to do a postorder traversal of the binary tree.
        void postorderTraversal() const;
        //Function to do a postorder traversal of the binary tree in an iterative way.
        void iterativePostorderTraversal() const;
        //Returns the height of the tree.
        int getTreeHeight() const;
        //Returns the number of nodes in the binary tree.
        int getTreeNodeCount() const;
        //Returns the number of leaves in the binary tree.
        int getTreeLeavesCount() const;
        //Deallocate the memory space occupied by the binary tree.
        //Post-condition: rootNodePtr = nullptr;
        void destroyTree();
};

template<typename ItemType>
class BinarySearchTree: public BinaryTreeInterface<ItemType>{
    public:
        //Function to determine if searchItem is in the binary search tree.
        //Post-condition: Returns true if searchItem is found in the binary search tree.
        //Otherwise, return false.
        bool search(const ItemType& searchItem) const;
        //Function to insert insertItem in the binary search tree.
        //Post-condition: If no node in the binary tree has the same value as insertItem
        //A node with the value insertItem is created and inserted in the binary search tree.
        void insert(const ItemType& insertItem);
        //Function to delete deleteItem from the binary search tree.
        //Post-condition: If a node with the same value as deleteItem is found, it 
        //is deleted from the binary search tree.
        void deleteNode(const ItemType& deleteItem);

    private:
        //Function to delete the node to which NodePtr points
        //Post-condition: The node to which NodePtr points is deleted from the binary
        //search tree.
        void deleteFromTree(TreeNode<ItemType>* &NodePtr);
};

int update(int& x){
    x = 5 * x;
    return x;
};

const int ARRAY_LEN = 14;

int main(){
    BinarySearchTree<int> BT;
    int insertList[ARRAY_LEN] = {60, 50, 70, 30, 53, 80, 35, 57, 75, 32, 40, 77, 48, 45};
    for (int i = 0; i < ARRAY_LEN; i++){
        BT.insert(insertList[i]);
    }
    cout << "Recursion version" << endl;
    BT.inorderTraversal();
    // BT.deleteNode(30);
    // BT.deleteNode(50);
    // BT.deleteNode(80);
    // BT.deleteNode(50);
    // BT.preorderTraversal();
    // BT.postorderTraversal();
    BT.inorderTraversal(update);
    BT.inorderTraversal();
    // cout << "Iterative version" << endl;
    // BT.iterativeInorderTraversal();
    // BT.iterativePreorderTraversal();
    // BT.iterativePostorderTraversal();
    return 0;
}

template<typename ItemType>
ItemType TreeNode<ItemType>::getVal(){
    return val;
}

template<typename ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getLeftLink() const{
    return leftLink;
}

template<typename ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getRightLink() const{
    return rightLink;
}

template<typename ItemType>
void TreeNode<ItemType>::setVal(ItemType val){
    this->val = val;
}

template<typename ItemType>
void TreeNode<ItemType>::setLeftLink(TreeNode<ItemType>* leftNodePtr){
    this->leftLink = leftNodePtr ;
}

template<typename ItemType>
void TreeNode<ItemType>::setRightLink(TreeNode<ItemType>* rightNodePtr){
    this->rightLink = rightNodePtr;
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getHeight(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr == nullptr){
        return 0;
    }
    else{
        return 1 + max(getHeight(NodePtr->getLeftLink), getHeight(NodePtr->getRightLink));
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::copyTree(TreeNode<ItemType>* &copiedTreeRoot, TreeNode<ItemType>* otherTreeRoot){
    if (otherTreeRoot == nullptr){
        copiedTreeRoot = nullptr;
    }
    else{
        copiedTreeRoot = new TreeNode<ItemType>;
        copiedTreeRoot->setVal(otherTreeRoot->getVal());
        copyTree(copiedTreeRoot->getLeftLink(), otherTreeRoot->getLeftLink());
        copyTree(copiedTreeRoot->getRightLink(), otherTreeRoot->getRightLink());
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::inorder(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr != nullptr){
        inorder(NodePtr->getLeftLink());
        cout << NodePtr->getVal() << " ";
        inorder(NodePtr->getRightLink());
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::inorder(TreeNode<ItemType>* NodePtr, int (*visit) (ItemType&)){
    if (NodePtr != nullptr){
        inorder(NodePtr->getLeftLink(), *visit);
        //since NodePtr->getVal() is a rvalue, it can't be used to bind to a int& type (should be lvalue)
        //NodePtr->val is a lvalue
        visit(NodePtr->val);
        inorder(NodePtr->getRightLink(), *visit);
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::preorder(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr != nullptr){
        cout << NodePtr->getVal() << " ";
        preorder(NodePtr->getLeftLink());
        preorder(NodePtr->getRightLink());
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::postorder(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr != nullptr){
        postorder(NodePtr->getLeftLink());
        postorder(NodePtr->getRightLink());
        cout << NodePtr->getVal() << " ";
    }
} 

template<typename ItemType>
bool BinaryTreeInterface<ItemType>::isEmpty() const{
    return (rootNodePtr == nullptr);
}

template<typename ItemType>
BinaryTreeInterface<ItemType>::BinaryTreeInterface(): 
    rootNodePtr(nullptr){}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::preorderTraversal() const{
    preorder(rootNodePtr);
    cout << endl;
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::inorderTraversal() const{
    inorder(rootNodePtr);
    cout << endl;
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::inorderTraversal(int (*visit) (ItemType&)){
    inorder(rootNodePtr, *visit);
}
template<typename ItemType>
void BinaryTreeInterface<ItemType>::postorderTraversal() const{
    postorder(rootNodePtr);
    cout << endl;
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getTreeHeight() const{
    return getHeight(rootNodePtr);
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getNodeCount(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr == nullptr){
        return 0;
    }
    else{
        return 1 + getNodeCount(NodePtr->getLeftLink()) + getNodeCount(NodePtr->getRightLink());
    }
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getLeavesCount(TreeNode<ItemType>* NodePtr) const{
    if (NodePtr->getLeftLink() == nullptr && NodePtr->getRightLink() == nullptr){
        return 0;
    }
    else{
        return 1 + getLeavesCount(NodePtr->getLeftLink()) + getLeavesCount(NodePtr->getRightLink());
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::destroy(TreeNode<ItemType>* NodePtr){
    if (NodePtr != nullptr){
        destroy(NodePtr->getLeftLink());
        destroy(NodePtr->getRightLink());
        delete NodePtr;
        NodePtr = nullptr;
    }
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getTreeNodeCount() const{
    return getNodeCount(rootNodePtr);
}

template<typename ItemType>
int BinaryTreeInterface<ItemType>::getTreeLeavesCount() const{
    return getLeavesCount(rootNodePtr);
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::destroyTree(){
    destroy(rootNodePtr);
}

template<typename ItemType>
BinaryTreeInterface<ItemType>::BinaryTreeInterface(const BinaryTreeInterface<ItemType>& otherBinaryTree){
    if (otherBinaryTree.rootNodePtr == nullptr){
        this->rootNodePtr = nullptr;
    }
    else{
        copyTree(this->rootNodePtr, otherBinaryTree.rootNodePtr);
    }
}

template<typename ItemType>
BinaryTreeInterface<ItemType>::~BinaryTreeInterface(){
    destroyTree();
}

template<typename ItemType>
const BinaryTreeInterface<ItemType>& BinaryTreeInterface<ItemType>::operator= (const BinaryTreeInterface<ItemType> &otherBinaryTree){
    //avoid self-copy
    if (this != &otherBinaryTree){
        if (this->rootNodePtr != nullptr){
            this->destroyTree();
        }
        if (otherBinaryTree.rootNodePtr == nullptr){
            this->rootNodePtr = nullptr;
        }
        else{
            copy(this->rootNodePtr, otherBinaryTree.rootNodePtr);
        }
    }
    return *this;
}

template<typename ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& searchItem) const{
    TreeNode<ItemType>* curPtr;
    bool found = false;
    if (this->rootNodePtr == nullptr){
        cout << "Cannot search an empty tree." << endl;
    }
    else{
        curPtr = this->rootNodePtr;
        while (curPtr != nullptr && !found){
            if (curPtr->getVal() == searchItem){
                found = true;
            }
            else if (curPtr->getVal < searchItem){
                curPtr = curPtr->getRightLink();
            }
            else{
                curPtr = curPtr->getLeftLink();
            }
        }
    }
    return found;
}

template<typename ItemType>
void BinarySearchTree<ItemType>::insert(const ItemType& insertItem){
    TreeNode<ItemType>* curPtr; //pointer to traverse the tree
    TreeNode<ItemType>* curParentPtr; //pointer behind the curPtr
    TreeNode<ItemType>* newNode; //pointer to create the new node.

    newNode = new TreeNode<ItemType>;
    newNode->setVal(insertItem);
    newNode->setLeftLink(nullptr);
    newNode->setRightLink(nullptr);

    if (this->rootNodePtr == nullptr){
        this->rootNodePtr = newNode;
    }
    else{
        curPtr = this->rootNodePtr;
        while (curPtr != nullptr){
            curParentPtr = curPtr;
            if (curPtr->getVal() == insertItem){
                cout << "The insert item is already in the list"
                     << "duplicates are not allowed." << endl;
            }
            else if (curPtr->getVal() > insertItem){
                curPtr = curPtr->getLeftLink();
            }
            else{
                curPtr = curPtr->getRightLink();
            }
        }
        if (curParentPtr->getVal() > insertItem){
            curParentPtr->setLeftLink(newNode);
        }
        else{
            curParentPtr->setRightLink(newNode);
        }
    }
}

template<typename ItemType>
void BinarySearchTree<ItemType>::deleteFromTree(TreeNode<ItemType>* &NodePtr){
    TreeNode<ItemType>* curPtr; //pointer to traverse the tree
    TreeNode<ItemType>* trailCurPtr; //pointer behind the curPtr;
    TreeNode<ItemType>* temp; //pointer to delete the node
    if (NodePtr == nullptr){
        cout << "Error: The node to be deleted is null." << endl;
    }
    //case1 : the node to be deleted is a leaf
    else if (NodePtr->getLeftLink() == nullptr && NodePtr->getRightLink() == nullptr){
        temp = NodePtr;
        NodePtr = nullptr;
        delete temp;
    }
    //case2: the node's left subtree is empty, connect its parent node to its right subtree
    else if (NodePtr->getLeftLink() == nullptr){
        temp = NodePtr;
        NodePtr = temp->getRightLink();
        delete temp;
    }
    //case3: the node's right subtree is empty, connect its parrent node to its left subtree
    else if (NodePtr->getRightLink() == nullptr){
        temp = NodePtr;
        NodePtr = temp->getLeftLink();
        delete temp;
    }
    //case4: the node's right and left node are non-empty
    //We find the largest element in the "left" subtree to fill the deleted node
    //(which is equivalent to finding the smallest element in the "right" subtree)
    //Thus, we traverse until the right pointer is null
    else{
        curPtr = NodePtr->getLeftLink();
        trailCurPtr = nullptr;
        while (curPtr->getRightLink() != nullptr){
            trailCurPtr = curPtr;
            curPtr = curPtr->getRightLink();
        }//end while: curPtr will be the largest node in the left subtree, trailCurPtr will be its parent node
        //Replace the deleted node with that value
        NodePtr->setVal(curPtr->getVal());
        //curPtr did not move
        if (trailCurPtr == nullptr){
            NodePtr->setLeftLink(curPtr->getLeftLink()); //set to nullptr
        }
        //connect its parent right link to the largest node's child 
        //the largest node has only left child
        else{
            trailCurPtr->setRightLink(curPtr->getLeftLink());
        }
        delete curPtr;
    }
}

template<typename ItemType>
void BinarySearchTree<ItemType>::deleteNode(const ItemType& deleteItem){
    TreeNode<ItemType>* curPtr = this->rootNodePtr; //pointer to traverse the tree
    TreeNode<ItemType>* trailCurPtr; //pointer behind the curPtr;
    bool found = false;
    if (this->rootNodePtr == nullptr){
        cout << "Cannot delete from the empty tree." << endl;
    }
    else{
        //search the deleteItem
        while (curPtr != nullptr && !found){
            if (curPtr->getVal() == deleteItem){
                found = true;
            }
            else{
                trailCurPtr = curPtr;
                if (curPtr->getVal() > deleteItem){
                    curPtr = curPtr->getLeftLink();
                }
                else{
                    curPtr = curPtr->getRightLink();
                }
            }
        }//end while: the curPtr is nullptr OR found is true and curPtr points the delete node
        if (curPtr == nullptr){
            cout << "The delete item is not in the tree." << endl;
        }
        else if (found){
            if (curPtr == this->rootNodePtr){
                deleteFromTree(this->rootNodePtr);
            }
            else if (trailCurPtr->getVal() > deleteItem){
                //set the parent node's left link to its right subtree
                deleteFromTree(trailCurPtr->leftLink);
            }
            else{
                deleteFromTree(trailCurPtr->rightLink);
            }
        }
    }
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::iterativeInorderTraversal() const{
    stack<TreeNode<ItemType>*> ptrStack;
    TreeNode<ItemType>* curPtr = this->rootNodePtr;
    while ((curPtr != nullptr) || (!ptrStack.empty())){
        if (curPtr != nullptr){
            ptrStack.push(curPtr);
            curPtr = curPtr->getLeftLink();
        }
        else{
            curPtr = ptrStack.top();
            ptrStack.pop();
            cout << curPtr->getVal() << " ";
            curPtr = curPtr->getRightLink();
        }
    }
    cout << endl;
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::iterativePreorderTraversal() const{
    stack<TreeNode<ItemType>*> ptrStack;
    TreeNode<ItemType>* curPtr = this->rootNodePtr;
    while ((curPtr != nullptr) || (!ptrStack.empty())){
        if (curPtr != nullptr){
            cout << curPtr->getVal() << " ";
            ptrStack.push(curPtr);
            curPtr = curPtr->getLeftLink();
        }
        else{
            curPtr = ptrStack.top();
            ptrStack.pop();
            curPtr = curPtr->getRightLink();
        }
    }
    cout << endl;
}

template<typename ItemType>
void BinaryTreeInterface<ItemType>::iterativePostorderTraversal() const{
    stack<TreeNode<ItemType>*> ptrStack;
    stack<int> valStack;
    //record the status of the pointer
    //v = 0: still traversing, v = 1: finish left subtree traversing, v = 2: finish right subtree traversing
    int v = 0;
    TreeNode<ItemType>* curPtr = this->rootNodePtr;
    if (curPtr == nullptr){
        cout << "Cannot traverse an empty tree." << endl;
    }
    else{
        ptrStack.push(curPtr);
        valStack.push(1);
        curPtr = curPtr->getLeftLink();
        while (!ptrStack.empty()){
            //not arrive at the end of the left subtree and still traversing
            if (curPtr != nullptr && v == 0){
                ptrStack.push(curPtr);
                valStack.push(1);
                curPtr = curPtr->getLeftLink();
            }
            //finish traversing OR arrive at the end of the left subtree
            else{
                curPtr = ptrStack.top();
                ptrStack.pop();
                v = valStack.top();
                valStack.pop();
                //finish traversing the left sub tree
                if (v == 1){
                    //start to traverse the right subtree
                    ptrStack.push(curPtr);
                    valStack.push(2);
                    curPtr = curPtr->getRightLink();
                    v = 0;
                }
                //finish traversing the right subtree
                //v == 2
                else{
                    cout << curPtr->getVal() << " ";
                }
            }
        }
    }
    cout << endl;
}