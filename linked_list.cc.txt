#include <iostream>
#include <string> 

struct Node {
  int key;
  Node* next;
}; 

void insert( Node*& head, int key) {
  Node * curr = new Node;
  curr->key  = key;
  curr->next = head;

  head = curr;
}

void print( Node* head ) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next ){ 
    std::cout << curr->key;
    if( curr->next != NULL ) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

// This function deletes the last element in the linked list.
// Pre-condition: The head of a linked list is provided.
// Post-condition: The last element of that linked list has been removed.
void delete_last_element( Node*& head )
{
    if (head == NULL) return;
    if (head->next == NULL) {
        delete head;
        head = NULL;
    }
    else {
        Node * beforeTail = head;
        Node * tail = head->next;
        while (tail->next != NULL) {
            beforeTail = tail;
            tail = tail->next;
            }
            delete tail;
            beforeTail->next = NULL;
    }
}

// This function inserts a key after a node with a given key.
// If there is no node with the given key, no action.
// Pre-condition: The head of a linked list,
// a key to indicate where to insert,
// and a new key to insert are provided.
// Post-condition: If a node with key is found, the linked list
// contains a new node (newKey) after that node.
void insert_after( Node* head, int key, int newKey )
{
        while (head->key != key) {
            if (head->next != NULL) 
            head = head->next;
            else return;
        }
        Node * newNode = new Node;   
        head->next = newNode;
        newNode->key = newKey;
}


// This function merges two linked lists.
// Pre-condition: Two linked lists (list1 and list2) are provided.
// Post-condition: A new linked list is returned that contains the keys
// of list1 and list2, starting with the first key of list1, then the
// first key of list2, etc. When one list is exhausted, the remaining
// keys come from the other list.
// For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
Node* interleave( Node* list1, Node* list2 )
{
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    else {
        Node * merged = NULL;
        Node * curr1 = list1;
        Node * curr2 = list2;
        Node * before = NULL;
        
        while (curr1 != NULL) {
            if (merged == NULL) {
                insert(merged, curr1->key);
                //delete_last_element(list1);
                insert_after(merged, curr1->key, curr2->key);
                //delete_last_element(list2);
                curr1 = curr1->next;
                before = curr2;
                curr2 = curr2->next;
            }
            else {
                insert_after(merged, before->key, curr1->key);
                //delete_last_element(list1);
                before = curr1;
                curr1  = curr1->next;
                if (curr2 != NULL) {
                    insert_after(merged, before->key, curr2->key);
                    //delete_last_element(list2);
                    before = curr2;
                    curr2 = curr2->next;
                }
            }
        }
        while (curr2 != NULL) {
            insert_after( merged, before->key, curr2->key);
            //delete_last_element(list2);
            before = curr2;
            curr2 = curr2->next;
        }
        return merged;
    }
}
    
    

int main() {

  Node * list1 = NULL;
  Node * list2 = NULL;
  Node * list3 = NULL;
  Node * list4 = NULL;

  insert( list1, 1);
  insert( list1, 2);
  insert( list1, 3);

  std::cout << "<A> List 1: ";
  print( list1 );

  insert( list2, 10);
  insert( list2, 9);
  insert( list2, 8);
  insert( list2, 7);
  insert( list2, 6);

  std::cout << "<B> List 2: ";
  print( list2 );

  delete_last_element( list1 );
  std::cout << "<C> List 1: ";
  print( list1 );

  delete_last_element( list1 );
  std::cout << "<D> List 1: ";
  print( list1 );

  delete_last_element( list1 );
  std::cout << "<E> List 1: ";
  print( list1 );

  delete_last_element( list1 );
  std::cout << "<F> List 1: ";
  print( list1 );

  insert(list1, 11);
  insert_after(list1, 11, 12);
  std::cout << "<G> List 1: ";
  print( list1 );

  insert_after(list1, 13, 14);
  std::cout << "<H> List 1: ";
  print( list1 );

  list4 = interleave(list1, list2);
  std::cout << "<I> List 4: ";
  print( list4 );

  list4 = interleave(list1, list3);
  std::cout << "<J> List 4: ";
  print( list4 );

  list4 = interleave(list3, list3);
  std::cout << "<K> List 4: ";
  print( list4 );

  return 0;
}
