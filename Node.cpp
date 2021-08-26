#include "Node.h"


template<typename ItemType>
Node<ItemType>::Node() : item(), next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr) {}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
	item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(shared_ptr<Node<ItemType>> nextNodePtr) {
	next = nextNodePtr;
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const {
	return item;
}

template<typename ItemType>
//ORIGINAL: Node<ItemType>* Node<ItemType>::getNext() const {
shared_ptr<Node<ItemType>> Node<ItemType>::getNext() const {
	return next;  //returns address of where it is pointing to
}