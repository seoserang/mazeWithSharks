#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<assert.h>
using std::cout;
using std::endl;

// Linked List object that maintains both head and tail pointers
// and the size of the list.  Note that you have to keep the head,
// tail and size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Type>
class List {
public:

	List();

	List(const List<Type>& other);

	List<Type>& operator=(const List<Type>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Type& item);
	void	push_back(const Type& item);
	void	add(int index, const Type& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Type	front() const;
	Type	rear() const;
	Type	get_at(int index) const;

	int		size() const;
	int		find(const Type& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	pop_at(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node* m_head;
	Node* m_tail;

	// Keep track of size of list
	int		m_size;
};


// List Implementation
//
//  Since List is a template class (which is not an actual 
//  class yet, not until we actually instantiate the list) 
//  we need to keep the implementation together with 
//  the definition.  There are ways to simulate having 
//  separate "implementation/definition" with templates, 
//  but they aren't necessary and can be confusing.
//

// Node definition
//		Already implemented, nothing to do here but to use it.
template<typename Type>
class List<Type>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Type item, Node* p, Node* n) : item(item), next(n), prev(p) {}

	Type  item;
	Node* next;
	Node* prev;
};


// --- List default constructor
//		Set head and tail pointer to point to nothing, size is zero
//		Already implemented, nothing to do.
template<typename Type>
List<Type>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}

// --- Copy constructor  
//		This should create an entirely new linked list with the same 
//		number of Nodes and the Values stored these Nodes in the same 
//		order as seen the other list’s Nodes.  This should not result 
//		in any memory leaks or aliasing.  
template<typename Type>
List<Type>::List(const List<Type>& other) {
	/* TODO 
	Traverse through the node and copy all the values
	1. use m_size the nodes then traverse through them 
	2. set values while traversing 
	*/
	m_head = nullptr; 
	m_tail = nullptr;
	m_size = 0;

	Node* n = other.m_head;
	while (n != nullptr) {
		push_back(n->item);
		n = n->next;
	}
}

// --- Overloaded assignment operator 
//		Causes the already existing linked list to be identical to the 
//		other linked list without causing any memory leaks or aliasing.
template<typename Type>
List<Type>& List<Type>::operator=(const List<Type>& other) {
	/* TODO */
	if (this == &other) {
		return *this;
	}
	if (m_head != nullptr) {
		Node* deleteNode;
//--- Get rid of the old pointers 
		deleteNode = m_head; 
		while (deleteNode != nullptr) {
			Node* n = deleteNode->next; 
			delete deleteNode;
			deleteNode = n;
		}
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
//--- Copy over the other list 
	Node* c = other.m_head;
	while (c != nullptr) {
		push_back(c->item);
		c = c->next;
	}
	return *this;
}

// --- List destructor
//		Traverses the nodes and deletes them without causing memory leaks
template<typename Type>
List<Type>::~List() {
	/* TODO */
	Node* curr = m_head;
	
		int count = 0;
		while (curr != nullptr) {
			Node * nextNode = curr->next;
			delete curr;
			curr = nextNode;
		}
}

// --- List print
//		Traverses list and prints items in list to console
//		Assumes << is overloaded for object Type.
//		
template<typename Type>
void List<Type>::print() const {
	/* TODO */
	
	if (m_head != nullptr) {
		Node* n = m_head;
		while (n != nullptr) {
			
			cout << n->item << endl;
			n = n->next;
		}
	}
}

// --- List empty
//		returns true if there are no items in the list
//		otherwise returns false.
template<typename Type>
bool List<Type>::empty() const {
	/* TODO */
	if (m_size == 0)
		return true;
	else
		return false;
}

// --- List push_front
//		Adds a new item to the front of the list
//		updates head, tail, and size accordingly.
//		
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::push_front(const Type& item) {
	/* TODO */
	// Need to implement the status of the next node at the moment the 
	// orginal head's prev is pointing to grabage , Fix the tail function 
	if (!empty()) { // case for not empty
		Node * p = new Node;
		m_head->prev = p; // set the orginal head to point to the new node. 
		p->next = m_head; // points the new head to the original
		p->prev = nullptr;
		m_head = p;
		p->item = item; 
	}
	else {//case for its empty
		Node* n = new Node;
		n->item = item; 
		n->next = nullptr;
		n->prev = nullptr; // Should happen regardless
		m_head = n; // Sets the m_head to the new node
		m_tail =n ; // it is the only node in the list so tail is n
	}
	m_size++;
}

// --- List push_back
//		Adds a new item to the rear of the list
//		updates head, tail, and size accordingly.
//
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::push_back(const Type& item) {
	/* TODO */
	if (empty())
		push_front(item);
	else {
		Node* curr = m_head;
		while (curr->next != nullptr) {//traverse to the end of the list 
			curr = curr->next;
		}
		Node* n = new Node;
		n->item = item;
		curr->next = n; // set the current end to point to the new node
		n->prev = m_tail;
		n->next = nullptr; //set the new node to point to null 
		m_tail = n; //set the new tail 
		m_size++;
	}
}

// --- List add
//		Adds a new item at the index indicated
//		updates head, tail, and size accordingly.
//
//		If the index less than or equal to zero add to the front.
//		If the index is greater than or equal to
//			the size of the list, add to the rear.
//		All other cases, add the item to the appropriate
//			location
//
template<typename Type>
void List<Type>::add(int index, const Type& item) {
	/* TODO
	1. check index then traverse to the index 
	2. add new node 
	3. repoint pointers 
	*/
	if (index <= 0)
		push_front(item);
	else if (index >= m_size)
		push_back(item);
	else {
		Node* curr = m_head;
		Node* temp;
		Node* n = new Node;
		n->item = item;
		
		int count = 0;
		while  (curr != nullptr) { //Traverse 
			if (count == index) { //break when index found
				temp = curr->prev; // get a copy of the current node prev
				n->next = temp->next; // set the new nodes tail to the next node in the list
				curr->prev = n; // then set tail of curr node prev to the new node
				n->prev = temp;
				temp->next = n;
				m_size++;
				break; 
			}
			count++;
			curr = curr->next;
		}	
	}
}

// --- List front
//		returns the first item in the list.
//
template<typename Type>
Type List<Type>::front() const {
	// Force check that the head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_head != nullptr);

	/* TODO */
	if (empty()) {
		Type Node; 
		return Node;
	}
	return m_head->item;
}

// --- List rear
//		returns the last item in the list
//
template<typename Type>
Type List<Type>::rear() const {

	// Force check that the tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_tail != nullptr);

	/* TODO */
	if (empty()) {
		Type node;
		return node;
	}
	
	return m_tail->item;
}

// --- List get_at
//		returns the item at index
//
template<typename Type>
Type List<Type>::get_at(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < m_size);

	/* TODO */
	if (empty()) {
		Type node; 
		return node;
	}
	else {
		int count = 0;
		Node* curr = m_head;
		while (curr != nullptr) { //Traverse to the required index
			if (count == index) { //break when index found
				return curr->item;
				break;
			}
			count++;
			curr = curr->next;
		}
	}
}

// --- List size
//		return the size of the list
template<typename Type>
int List<Type>::size() const {
	return m_size;
}

// --- List find
//		Traverses the list to see if the item is in the list
//		if it is return the index of that item, otherwise
//		return -1. Assumes the == operator is overloaded for
//		object Type.
template<typename Type>
int List<Type>::find(const Type& item) const {

	/* TODO */
	int count = 0;
	Node* curr = m_head;
	while (curr != nullptr) { //Traverse 
		if (item == curr->item) { //break when index found
			
			return count;
		}
		count++;
		curr = curr->next;
	}
	return -1;
}

// --- List pop_front
//		Removes the first item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least two cases where the list: is empty, 
//		has one or more items.
//		
template<typename Type>
bool List<Type>::pop_front() {

	/* TODO */
	if (m_size == 1) { //Do nothing
		delete m_head;                       
		m_head = nullptr;
		m_tail = nullptr;
		m_size--;                       
		return true;
	}
	if (m_size > 1) {
		Node* n = m_head; // Sets the temp to point to the next node
		m_head = n->next; // set the head to point to the next item in the list
		delete n;
		m_head->prev = nullptr; // reset the head.
		m_size--;
		return true;
	}
	return false;
}

// --- List pop_rear
//		Removes the last item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least three cases where the list: is empty, 
//		has one item, has two or more items.
//	
template<typename Type>
bool List<Type>::pop_rear() {
	/* TODO */
	if (m_size==0) { //Do nothing
		cout << "The List is empty!" << endl;
		return false;
	}
	else if (m_size == 1) { 
		return pop_front();
	}
	else if (m_size > 1){
		Node* curr = m_tail;
		m_tail = curr->prev; //set the tail of new last node
		m_tail->next = nullptr; //Set the tail 
		m_size--;
		delete curr;
		
		return true;
	}
	
}

// --- List pop_at
//		Removes the item at the index returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly. If the index is
//		out of bounds return false.
//
template<typename Type>
bool List<Type>::pop_at(int index) {

	/* TODO */
	if (index > m_size) { // checks if index is in bounds
		cout << "Index is out of bounds" << endl;
		return false;
	}
	else if (empty()) { //check if list empty
		cout << "Empty List" << endl;
		return false;
	}
	else if (index < 0) { // if index is less that 0 ju
		cout << "Out of bounds!" << endl;
		return false;
	}
	else if (index == 0) {
		return pop_front();
	}
	else {
		Node* curr = m_head; 
		Node* temp, * removeNode;
		int count = 0;
		while (curr != nullptr) { //Traverse 
			if (curr->next == nullptr) { //after all the logics, last item must be the item to be deleted
				return pop_rear();
			}
			else if (count == index) { //break when index found
				temp = curr->prev; // get a copy of the current node prev
				removeNode = curr;
				curr->next->prev = temp;
				temp->next = curr->next;
			
				delete removeNode;

				m_size--;
				return true;
			}
			count++;
			curr = curr->next;
		}
	}
}

#endif 