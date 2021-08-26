#include <cstddef>
#include "Node.h"
#include "LinkedBag.h"

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}


//this whole constructor is for copying a pre-existing made linked list into a new linked list
template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
	itemCount = aBag.itemCount;

//	  ORIGINAL: Node<ItemType>* origChainPtr = aBag.headPtr;
//    FIRST-ATTEMPT: weak_ptr<ItemType> origChainPtr = aBag.headPtr;
   shared_ptr<Node<ItemType>> origChainPtr = aBag.headPtr;

	if (origChainPtr == nullptr) {
		headPtr = nullptr; 
	}
	else {
//		 ORIGINAL:  headPtr = new Node<ItemType>();
        headPtr = make_shared<Node<ItemType>>();
		headPtr->setItem(origChainPtr->getItem());

//		Node<ItemType>* newChainPtr = headPtr;
        shared_ptr<Node<ItemType>> newChainPtr = headPtr;

        //reassinging the pointer from the head to the next node in the list
		origChainPtr = origChainPtr->getNext();

		//while the headPtr is not null
		while (origChainPtr != nullptr)
		{
		    //store a copy of the data within the second node
			ItemType nextItem = origChainPtr->getItem();
			//creating a new node that stores the same data as the head
//			ORIGINAL: Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
           shared_ptr<Node<ItemType>> newNodePtr = make_shared<Node<ItemType>>(nextItem);
			//setting headptr.next to that new 'copyCat' node
			newChainPtr->setNext(newNodePtr);
			//now reassinging that new 'copyCat' node to the next node
			newChainPtr = newChainPtr->getNext();
			//setting the origin pointer to the next node
			origChainPtr = origChainPtr->getNext();
		} 

		newChainPtr->setNext(nullptr);
	}
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag() {
    cout<< "--->>>>> A Bag Item is Destroyed --->>>>>";
	clear();
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
	return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
//	ORIGINAL: Node<ItemType>* nextNodePtr = new Node<ItemType>();
    shared_ptr<Node<ItemType>> nextNodePtr = make_shared<Node<ItemType>>();
	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  
	headPtr = nextNodePtr;
	itemCount++;
	return true;
}

template<typename ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
	std::vector<ItemType> bagContents;
//	ORIGINAL:  Node<ItemType>* curPtr = headPtr;
    shared_ptr<Node<ItemType>> curPtr = headPtr;
	int counter = 0;

	while ((curPtr != nullptr) && (counter < itemCount)) {
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}
	return bagContents;
}

//for removing a specific item
template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
//	ORIGINAL: Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    shared_ptr<Node<ItemType>> entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);

	if (canRemoveItem) {
		entryNodePtr->setItem(headPtr->getItem());
//		ORIGINAL: Node<ItemType>* nodeToDeletePtr = headPtr;
        shared_ptr<Node<ItemType>> nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
//		ORIGINAL: delete nodeToDeletePtr;   <-NOT NEEDED due to shared pointer
		nodeToDeletePtr = nullptr;

		itemCount--;
	}

	return canRemoveItem;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear() {
//	ORIGINAL: Node<ItemType>* nodeToDeletePtr = headPtr;
    shared_ptr<Node<ItemType>> nodeToDeletePtr = headPtr;

	while (headPtr != nullptr) {
		headPtr = headPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
//		ORIGINAL: delete nodeToDeletePtr;           //NOT NEEDED due to smart pointer (shared)
		nodeToDeletePtr = headPtr;
	}

	itemCount = 0;
} 

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int frequency = 0;
	int counter = 0;
//	ORIGINAL: Node<ItemType>* curPtr = headPtr;
    shared_ptr<Node<ItemType>> curPtr = headPtr;

	while ((curPtr != nullptr) && (counter < itemCount)) {
		if (anEntry == curPtr->getItem()) {
			frequency++;
		} 
		counter++;
		curPtr = curPtr->getNext();
	}

	return frequency;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
//ORIGINAL: Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
shared_ptr<Node<ItemType>> LinkedBag<ItemType>::getPointerTo(const ItemType & anEntry) const {
	bool found = false;
//	ORIGINAL: Node<ItemType>* curPtr = headPtr;
    shared_ptr<Node<ItemType>> curPtr = headPtr;

	while (!found && (curPtr != nullptr)) {
		if (anEntry == curPtr->getItem()) {
			found = true;
		}
		else {
			curPtr = curPtr->getNext();
		}
	}

	return curPtr;
} 