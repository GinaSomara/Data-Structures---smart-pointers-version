#pragma once
#include <cstdlib>
#include <iostream>
#include "Node.cpp"
#include "BagInterface.h"
using std::cout;

template<typename ItemType>
class LinkedBag : public BagInterface<ItemType> {

/*--------------------------CSC340-------------------------------------*/
public:
	bool removeSecondNode340();
	bool addEnd340(const ItemType&);  //need to give item name in implementation
	int getCurrentSize340Iterative() const;
	int getCurrentSize340Recursive() const;
	int getCurrentSize340RecursiveNoHelper() const;
	int getFrequencyOf340Recursive(const ItemType&) const;   //need to give item name in implementation
	int getFrequencyOf340RecursiveNoHelper(const ItemType&) const;   //need to give item name in implementation
    ItemType removeRandom340();
private:
//	ORIGINAL: int getCurrentSize340RecursiveHelper(Node<ItemType>*) const; // if needed
//	ORIGINAL: int getFrequencyOf340RecursiveHelper(Node<ItemType>*, const ItemType&) const; // if needed
    int getCurrentSize340RecursiveHelper(shared_ptr<Node<ItemType>>) const;
    int getFrequencyOf340RecursiveHelper(shared_ptr<Node<ItemType>>, const ItemType&) const;
/*----------------------------------------------------------------------*/

public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>&);
	virtual ~LinkedBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType&);
	bool remove(const ItemType&);
	void clear();
	bool contains(const ItemType&) const;
	int getFrequencyOf(const ItemType&) const;
	std::vector<ItemType> toVector() const;

private:
//	    ORIGINAL: Node<ItemType>* headPtr{ nullptr }; // Pointer to first node
    shared_ptr<Node<ItemType>> headPtr{ nullptr };
	int itemCount{ 0 };					// Current count of bag items

	// pointer to the node or the null pointer
//	ORIGINAL: Node<ItemType>* getPointerTo(const ItemType&) const;
    shared_ptr<Node<ItemType>> getPointerTo(const ItemType&) const;
};




