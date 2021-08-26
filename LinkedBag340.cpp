#include "LinkedBag.h"
#include "Node.h"

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340()
{
    try
    {   //1)  second node in list
//       ORIGINAL: Node<ItemType> *tempNode = headPtr->getNext();
        shared_ptr<Node<ItemType>> tempNode = headPtr->getNext();
        //2)  headPtr will now point to third node in list, making it the second node
        headPtr->setNext(headPtr->getNext()->getNext());
        //3)  deleting orphaned node in memory
//        delete tempNode;       NOT needed since pointer is now smart
        tempNode = nullptr;

        itemCount--;
    }catch(...){   //if fails
       cout<< "EXCEPTION THROWN!";
        return false;
    }
    return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& anItem)
{
    try{
        //nextPtr is already set to null during construction
//      ORIGINAL: Node<ItemType>* newNodePtr = new Node<ItemType>(anItem);
        shared_ptr<Node<ItemType>> newNodePtr = make_shared<Node<ItemType>>(anItem);


        //a tempNode to aid in iteration, starting @ second node
//       ORIGINAL: Node<ItemType>* tempNode = headPtr;
        shared_ptr<Node<ItemType>> tempNode = headPtr;

        //need to iterate through the list in order to add onto end
        for(int i=0; i < itemCount-1 ; i++)
        {
            tempNode=tempNode->getNext();
            //for last node, add in new one
            if(i == (itemCount-2))
            {
                //setting last nodes nextPr to newly created node
                tempNode->setNext(newNodePtr);
            }
        }
        tempNode = nullptr;  //good practice
    } catch (...) {
        cout<< "EXCEPTION THROWN!";
        return false;
    }
    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
    int counter{0};

    //initialing checking
    if(headPtr == NULL)
        return 0;
    //add one so head gets counted in total count
    else counter++;

    //tempNode starting @ second node
//  ORIGINAL:  Node<ItemType>* tempNode = headPtr->getNext();
    shared_ptr<Node<ItemType>> tempNode = headPtr->getNext();

    while(tempNode != NULL)  //while not NULL
    {
        counter++;
        //iterating through the nodes
        tempNode = tempNode->getNext();
    }
    return counter;
}

//======Recursive Methods=====//
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const
{
    if(headPtr == NULL)  return 0;
    else  return getCurrentSize340RecursiveHelper(headPtr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const
{
    static int count {0};
//   ORIGINAL: static Node<ItemType>* nodePtr = headPtr;
    static shared_ptr<Node<ItemType>> nodePtr = headPtr;
    //base case
    if (nodePtr == NULL) return count;

    count++;

    nodePtr = nodePtr->getNext();

    return getCurrentSize340RecursiveNoHelper();
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& itemName) const
{
    if(headPtr == NULL)  return 0;
    else  return getFrequencyOf340RecursiveHelper(headPtr, itemName) ;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& itemName) const
{
    static int freqCounter {0};
//    ORIGINAL: static Node<ItemType>* nodePtr{headPtr} ;
    static shared_ptr<Node<ItemType>> nodePtr = headPtr;

    //base case and resets
    if(nodePtr == headPtr) freqCounter = 0; //resetting counter for each new call from main
    if(nodePtr == NULL)   //base case, end of list
    {
        nodePtr = headPtr;   //resetting nodePtr for each new call from main
        return freqCounter;
    }

    if(itemName == nodePtr->getItem())
        freqCounter++;

    nodePtr = nodePtr->getNext();
    return getFrequencyOf340RecursiveNoHelper(itemName);
}

//function works by replacing entry to be removed with the head info, then reassigning head
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340()
{
    ItemType randomEntry; //return item

    srand(time(0));   //getting random seed
    int randNode = rand()%itemCount;

//   ORIGINAL: Node<ItemType>* tempNode {headPtr};
    shared_ptr<Node<ItemType>> tempNode = headPtr;
    //finding our random node, to remove, and replace it with the head of the list
    for(int i{0} ; i < itemCount ; i++)
    {
        if(i == randNode)  //when node is found
        {
            randomEntry = tempNode->getItem();
            tempNode->setItem(headPtr->getItem());
            headPtr = headPtr->getNext();
            itemCount--;
            tempNode = tempNode->getNext();
            break;
        }
        else
            tempNode = tempNode->getNext();
    }

    tempNode = nullptr;
    return randomEntry;
}

//======Helpers=====//
template<typename ItemType>
//ORIGINAL: int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* nodePtr) const
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(shared_ptr<Node<ItemType>> nodePtr) const
{
    static int counter {0};

    if(nodePtr == NULL)   //base case
        return counter;
    else {
        counter++;
        return getCurrentSize340RecursiveHelper(nodePtr->getNext());
    }
}

template<typename ItemType>
//ORIGINAL: int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* nodePtr, const ItemType& itemName) const
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(shared_ptr<Node<ItemType>> nodePtr, const ItemType& itemName) const
{
    //since called multiple times in main, need to reset every call
    static int freqCounter {0};
    if(nodePtr == headPtr) freqCounter = 0;

    if(nodePtr == NULL) //base case
        return freqCounter;

    if(itemName == nodePtr->getItem())
        freqCounter++;

    return getFrequencyOf340RecursiveHelper(nodePtr->getNext(), itemName);
}