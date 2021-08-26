#pragma once
#include<memory>
using std::shared_ptr;

template<typename ItemType>
class Node {
public:
	Node();
	Node(const ItemType&);
	Node(const ItemType&, Node<ItemType>*);
	void setItem(const ItemType&);
	void setNext(shared_ptr<Node<ItemType>>);
	ItemType getItem() const;
//	ORIGINAL: Node<ItemType>* getNext() const;
    shared_ptr<Node<ItemType>> getNext() const;

private:
	ItemType        item{};			 // A data item
//	ORIGINAL: Node<ItemType>* next{ nullptr }; // Pointer to next node
    shared_ptr<Node<ItemType>> next {nullptr};
};