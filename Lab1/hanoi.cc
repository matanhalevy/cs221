#include <cstdlib>   // for atoi
#include <iostream>

void moveDisks(int n, const char* peg1, const char* peg2, const char* peg3);
const char* pegA;
const char* pegB;
const char* pegC;

int main() {
	int number_of_disks;
	std::cout << "Please enter the number of disks: " << std::endl;
	std::cin >> number_of_disks;
	moveDisks(number_of_disks, "peg A", "peg B", "peg C");
	return 0;
  }



void moveDisks(int n, const char* pegA, const char* pegB, const char* pegC){
	if (n > 0){
	moveDisks((n - 1), pegA, pegC, pegB);
	std::cout<< "Move disk " << n << " from " << pegA << " to " << pegC << "." << std::endl;
	moveDisks((n - 1), pegB, pegA, pegC);
	}
}

