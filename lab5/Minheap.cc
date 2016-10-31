#include "Minheap.h"
#include <iostream>
#include <cassert>
#include <iomanip>

/**
 * Construct a minheap from the supplied elements (no extra capacity) 
 */ 
Minheap::Minheap(int* elements, int num_elements) {
	_capacity = num_elements; 
	_size = num_elements; 
	_heap = new int[ _capacity ]; 
	for (int ii=0; ii < _size; ++ii) {
		_heap[ ii ] = elements [ ii ]; 
	}
	heapify(); 
}
/**
 * Construct an empty minheap with given capacity   
 */ 
Minheap::Minheap(int capacity) {
	_capacity = capacity; 
	_size = 0; 
	_heap = new int[ _capacity ]; 
}
/**
 * Default constructor 
 */ 
Minheap::Minheap() {
	_capacity = DEFAULT_CAPACITY; 
	_size = 0; 
	_heap = new int[ _capacity ]; 
}

/** Destructor */ 
Minheap::~Minheap() {
    delete[] _heap; 
}

/**
 * Inserts element into the heap 
 * PRE: _size < _capacity 
 * POST: _size has been incremented by 1 
 * POST: _heap is a valid minimum heap 
 */ 
void Minheap::insert(int element) { 
	assert( _size < _capacity ); 
	// ******** TO BE COMPLETED ********
	// ******** you cannot use heapify()
	//bool match = false;
	/*for(int i = 0; i < _size; i++) {
		if(element == _heap[i]){
			match = true;
		}
	}*/
	//if (!match) {
		//if(!(_size == _capacity)) {
		_size++;
		_heap[_size - 1] = element;
		//_heap[_size] = element;
		swap_up(_size - 1);
		//}
		//_size++;
	//}
	
	
} 
 
/**
 * Pops top element from heap and returns its value
 * PRE: _size > 0 
 * POST: _size has been decremented by 1
 * POST: _heap is a valid minimum heap 
 * RETURNS: value of old top element
 */ 
int Minheap::delete_min() { 
	assert( _size > 0 ); 
	
	// ******** TO BE COMPLETED ********
	// ******** you cannot use heapify() 
	//std:: cout << "deleting : " << _heap[0] << " " << std:: endl;
	int temp = _heap[0];
	_heap[0] = _heap[_size - 1];
	//_heap[0] = _heap[_size];
	_size--;
	swap_down(0);
	print_tree(0,0);
	//std:: cout << "current size : " << _size << " " << std:: endl;
	
	
	 
	return temp; // ******** REMOVE THIS LINE 
} 
 
/**
 * Remove all entries with value-to-remove from the heap
 * POST: no element in the heap has value equal to value-to-remove 
 * POST: _heap is a valid minimum heap (with correct _size)  
 */ 
void Minheap::remove_matching(int value_to_remove) {
	// ******** TO BE COMPLETED ********
	// ******** heapify() can be used 
	int i = 0;
	while(i <_size) {
		if(_heap[i] == value_to_remove) {
			_heap[i] = _heap[_size - 1];
			// move to bot
			_size--;
			// decrement size
			//heapify();
			// maintain heap
			//remove_matching(value_to_remove);
			// call it on the subheap
			// recursive call on the advice of Shaaban
		}
		else {
			i++;
		}
	}
	
	
	
	
	//call at end
	heapify();
	
	
	
}

// print heap as tree (public method sets up call to recursive method) 
void Minheap::print_tree() {
	
	// originally given
	print_tree(0, 0); 
}
/** 
 * Print the tree rooted at ix 
 * PRE: ix might be "out of bounds" 
 * PRE: level is the depth of recursion (plus 1 each time)
 * POST: the tree rooted at ix has been printed
 */
void Minheap::print_tree(int ix, int level) {
	// BASE CASE we're "out of bounds" 
	if (ix < 0 || ix >= _size) return; 
	// calculate the "pointers" to the left and right children 
	// ******** TO BE COMPLETED ******** 
	
	// from the BST lab
	int right_pos = (2*ix) + 2;
	int left_pos = (2*ix) + 1;
	
	print_tree(right_pos, level+1);
	std::cout << std::setw( 3 * level ) << ""; // output 3 * level spaces
	std::cout << _heap[ix] << std::endl;
	print_tree(left_pos, level+1);
	
	
	
}
// print heap as array 
void Minheap::print_array(){ 
	for (int ii = 0; ii < _size; ++ ii)
		std::cout << _heap[ ii ] << " ";
	std::cout << std::endl;
}
// heapify as a method of a Class (compare with version in example.cc) 
void Minheap::heapify() {
	int last_parent = ( _size - 2) / 2; 
	for (int ii = last_parent; ii >= 0; ii --){
		swap_down( ii );
	}
}
// swap_down 
void Minheap::swap_down(int ix) {
	int leftChild = (2 * ix) + 1;
	int rightChild = (2 * ix) + 2;
	int min = ix;
	// find who holds smallest value (ix or one of its two children)
	if (leftChild < _size && _heap[leftChild] < _heap[min])
		min = leftChild;
	if (rightChild < _size && _heap[rightChild] < _heap[min])
		min = rightChild;
	// if a child holds smallest value, 
	// swap ix's element to that child and recurse 
	if (min != ix) {
		int temp = _heap[ix]; 
		_heap[ix] = _heap[min]; 
		_heap[min] = temp; 
		swap_down(min);
	}
}
void Minheap::swap_up(int ix) {
	if (ix < 1) return; // BASE CASE 
	int parent = (ix - 1) / 2; 
	if (_heap[ix] < _heap[parent] ){
		int temp = _heap[ix]; 
		_heap[ix] = _heap[parent]; 
		_heap[parent] = temp; 
		swap_up(parent); 
	}
}

bool Minheap::isEmpty() {
	return ( _size == 0 ); 
}

/** This will be almost exactly the same as your print_tree(int, int)
* EXCEPT recursively call visit_tree( rightChild, level + 1, v)
* instead of print_tree( rightChild, level + 1 )
* AND the same for the recursive call to the leftChild of course
* AND v.visit( _heap, ix, level )
* instead of using std::cout to print some spaces and _heap[ix]
*/
/*void Minheap::visit_tree(int ix, int level, Visitor& v);

// BASE CASE we're "out of bounds" 
	if (ix < 0 || ix >= _size) return; 
	// calculate the "pointers" to the left and right children 
	// ******** TO BE COMPLETED ******** 
	
	// from the BST lab
	int right_pos = (2*ix) + 2;
	int left_pos = (2*ix) + 1;
	
	visit_tree(right_pos, level+1, v);
	std::cout << std::setw( 3 * level ) << ""; // output 3 * level spaces
	std::cout << _heap[ix] << std::endl;
	visit_tree(left_pos, level+1, v);*/

// getters 
int Minheap::get_size() {
	return _size; 
}
int Minheap::get_capacity() {
	return _capacity; 
}
int* Minheap::get_heap() {
	int* result = new int[ _capacity ];
	for (int ii=0; ii < _size; ++ii){ 
		result[ii] = _heap[ii]; 
	}
	for (int ii = _size; ii < _capacity; ++ii) {
		result[ii] = 0; 
	}
	return result; 
}


// visit_heap (Unit test version of print_tree)
void Minheap::visit_tree(Visitor& v) {
	visit_tree(0, 0, v); 
}
/** 
 * This will be almost exactly the same as your print_tree(int, int)
 * EXCEPT recursively call visit_tree( rightChild, level + 1, v)  
 *        instead of       print_tree( rightChild, level + 1 )
 * AND the same for the recursive call to the leftChild of course 
 * AND v.visit( _heap, ix, level ) 
 * instead of using std::cout to print some spaces and  _heap[ix] 
 */
void Minheap::visit_tree(int ix, int level, Visitor& v) {
	// BASE CASE we're "out of bounds" 
	if (ix < 0 || ix >= _size) return; 
	// calculate the "pointers" to the left and right children 
	// ******** TO BE COMPLETED ******** 
	
	// from the BST lab
	int right_pos = (2*ix) + 2;
	int left_pos = (2*ix) + 1;
	
	visit_tree(right_pos, level+1, v);
	/*std::cout << std::setw( 3 * level ) << ""; // output 3 * level spaces
	std::cout << _heap[ix] << std::endl;*/
	v.visit(_heap, ix, level);
	visit_tree(left_pos, level+1, v);
	
	
	
}

