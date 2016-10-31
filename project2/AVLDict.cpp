#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an unsorted linked list.
//
AVLDict::AVLDict() {
  root = NULL;

  // Initialize array of counters for depth statistics
  depth_stats = new int[MAX_STATS]();
}

void AVLDict::destructor_helper(node * x) {
  if (x == NULL) return; // Nothing to destroy.
  destructor_helper(x->left);
  destructor_helper(x->right);
  delete x->key;
  delete x;
}

AVLDict::~AVLDict() {
  // Clean up the tree.
  // This is most easily done recursively.
  destructor_helper(root);

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Depth Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << depth_stats[i] << endl;
  delete [] depth_stats;
}


bool AVLDict::find_helper(node *r, string keyID, PuzzleState *&pred, int depth) {
  if (r==NULL) {
    if (depth<MAX_STATS) depth_stats[depth]++;
    return false; // Didn't find it.
  }
  if (keyID == r->keyID) {
    if (depth<MAX_STATS) depth_stats[depth]++;
    pred = r->data; // Got it!  Get the result.
    return true;
  }
  if (keyID < r->keyID) return find_helper(r->left, keyID, pred, depth+1);
  else return find_helper(r->right, keyID, pred, depth+1);
}

bool AVLDict::find(PuzzleState *key, PuzzleState *&pred) {
  return find_helper(root, key->getUniqId(), pred, 0);
}

bool AVLDict::update_height( node * x ) {
  //
  // Recalculates the height of x from the height of its children.
  // Returns true iff the height of x changes.
  //

  // :TODO: Write this function!
	if (x == NULL) return false;
	int m = (height(x->left) > height(x->right)) ? height(x->left) + 1 : height(x->right) + 1;
	if (x->height != m) {
		x->height = m;
		return true;
	}
	return false;
}

void AVLDict::rotate_left( node *& a ) {
  // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Rotate Left: " << a->keyID << std::endl;
#endif
// End of "DO NOT CHANGE" Block

  // :TODO: Write this function!
assert(a != NULL);
assert(a->right != NULL);
node * temp = a->right;
a->right = temp->left;
temp->left = a;
update_height(a);
update_height(temp);
a = temp;

}

void AVLDict::doublerotate_left(node *& x){
	assert(x != NULL);
	rotate_right(x->right);
	rotate_left(x);
}

void AVLDict::doublerotate_right(node *& x){
	assert(x != NULL);
	rotate_left(x->left);
	rotate_right(x);
}


void AVLDict::rotate_right( node *& b ) {
  // "rotates" the subtree rooted at b to the right (clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
cout << "Rotate Right: " << b->keyID << endl;
#endif
// End of "DO NOT CHANGE" Block

  // :TODO: Write this function!
assert(b != NULL);
assert(b->left != NULL);
node * temp = b->left;
b->left = temp->right;
temp->right = b;
update_height(b);
update_height(temp);
b = temp;
}

void AVLDict::balance(node *& x){
	if (height(x->right) - height(x->left) > 1){
		if (height(x->right->left) > height(x->right->right)){
			doublerotate_left(x);
		}
		else rotate_left(x);
	}
	if (height(x->left) - height(x->right) > 1){
		if (height(x->left->right) > height(x->left->left)){
			doublerotate_right(x);
		}
		else rotate_right(x);
	}
}

void AVLDict::insert(node *x, node * & root){
	if (root == NULL) {
		root = x;
		return;
	}
	// either go to the left, or to the right, but ignore if already in tree
	if (x->keyID < root->keyID) {
		insert(x, root->left);
	}
	// 2014W2 if key == root->key then ignore it (do not insert duplicate) 
	else if (x->keyID > root->keyID) {
		insert(x, root->right);
	}
	if (update_height(root)) balance(root);
}

// You may assume that no duplicate PuzzleState is ever added.
void AVLDict::add(PuzzleState *key, PuzzleState *pred) {
	node* result = new node;
	result->key = key;
	result->keyID = key->getUniqId();
	result->data = pred;
	result->height = 0;
	result->left = NULL;
	result->right = NULL;
	insert(result, root);
	
}

#endif 
