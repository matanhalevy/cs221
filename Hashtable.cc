#include <cstdlib>
#include <iostream>
#include <cassert> 
#include <vector> 
#include "Hashtable.h"

using namespace std; 

#define HUGE_FLOAT 9999999.9999999 

Hashtable::Hashtable(int size) {
	//constructor
	int prime = nextPrime( size ); 
	_size = size;
	if (prime != size) { 
	  cout << "Warning: size = " << size << " is not a prime number."; 
//	  cout << "Using " << prime << " instead." << endl; 
//	  _size = prime; 
	}
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	_table = new int [ _size ];
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}
void Hashtable::clear(void) {
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}    
    

Hashtable::~Hashtable() {
	//deconstructor
	delete[] _table;
}

void Hashtable::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	_totalProbes += p;
	_numInserts += 1;
}

void Hashtable::printStats() {
	cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			_totalProbes << "/" << _numInserts;
	cout <<", size = "<< _size;
	cout <<", failures = " << _numFailures << endl;
}

float Hashtable::probeRate() {
    if ( _numInserts == 0 ) return HUGE_FLOAT;  
	return (float)_totalProbes / (float)_numInserts;
}

int Hashtable::hash(int k) {
	return k % _size;
}

int Hashtable::hash2(int k, int iter) {
	return iter - (k % iter);
}

void Hashtable::qinsert(int k) {	
    
    int index = hash(k);
	int probe = 1;
	if (_table[index] == EMPTY) {
		_table[index] = k;
		tallyProbes(probe);
		return;
	}
	int quad = 1;
	while (_table[index] != EMPTY) {
		if (_numInserts == _size) break; //if it's completely filled up, break;	
		index = (hash(k) + quad*quad) % _size;
		probe++;
		if (_table[index] == EMPTY) {
			_table[index] = k;
			tallyProbes(probe);
			return;
		}
		if (probe == _size) {   
            cout << "Probing limit exceeded." << endl; 
			_numFailures+=1;
			return;
		}
		
		quad++;
	}

    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: qinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

void Hashtable::linsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with linear probing and hash(k) = k % _size.

    // ************* ADD YOUR CODE HERE *******************
    int index = hash(k);
	int probe = 1;
	if (_table[index] == EMPTY) {
		_table[index] = k;
		tallyProbes(probe);
		return;
	}
	int lin = 1;
	while (_table[index] != EMPTY) {
		if (_numInserts == _size) break;
		index = (hash(k) + lin) % _size;
		probe++;
		if (_table[index] == EMPTY) {
			_table[index] = k;
			tallyProbes(probe);
			return;
		}
		lin++;
	}
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

void Hashtable::dinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with double hashing. 
	// Use the existing hash(int) function
	// and implement hash2(int, int) as well.

    // ************* ADD YOUR CODE HERE *******************
    int index = hash(k);		
    int probe = 1;
    if (_table[index] == EMPTY) {
        _table[index] = k;
        tallyProbes(probe);
        return;
    }
	int x = 1;
    while (_table[index] != EMPTY) {
		if (_numInserts == _size) break;
		index = (hash(k) + x * hash2(k, 5)) % _size;
        probe++;
        if (_table[index] == EMPTY){
            _table[index] = k;
            tallyProbes(probe);
            return;
        }
		if (probe == _size) {   
            cout << "Probing limit exceeded." << endl; 
			_numFailures+=1;
			return;
		}
        x++;
    }
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: dinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

void Hashtable::print() {
	// Print the content of the hash table.

	for (int i=0; i<_size; i++) {
		cout<<"["<<i<<"] ";
		if (_table[i] != EMPTY)
			cout << _table[i];
		cout << endl;
	}
}

// 

int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if ((n == 2) || (n == 3) || (n == 5)) return true;
    if (n % 2 == 0) return false;  
    if (n % 3 == 0) return false;  
    if (n % 5 == 0) return false;  
    return isPrime( n, 7 ); 
}
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    assert( (divisor % 2) == 1 ); // divisor is odd  
    if ((divisor % 10) == 3) return isPrime( n, divisor + 4 ); 
    return isPrime( n, divisor + 2 ); 
}
void Hashtable::getHashVector(std::vector<int>& hashVector ){ 
    hashVector.clear(); 
    for (int ii=0; ii < _size; ii++) { 
        hashVector.push_back( _table[ii] ); 
    }
} 
int Hashtable::getSize() { 
    return _size; 
} 
int Hashtable::getInserts(){
    return _numInserts; 
}
int Hashtable::getFailures(){
    return _numFailures; 
} 
int Hashtable::getProbes(){
    return _totalProbes;
}


