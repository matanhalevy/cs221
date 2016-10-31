#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comps = 0 ;
int count = 0;
void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a]) {
			swap(x[++m], x[i]);

		}
		comps++;
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

int qc (int n){

	if (n <= 1){
	return 0;
	}
	else{
	int p = randint(0,n-1); // pivot
	count = n-1 + qc(p) + qc(n - 1 -p);

	}
	return count;
}
#define NN 100

int main(int argc, char *argv[]) {
	srand(time(0));
  for (int i = 0; i < 100; i++){
	// change the following code
	x = new int[NN];
	for (int i=0; i<NN; ++i) {
		x[i] = rand() % NN;
	}

	quicksort(0, NN-1);
	for (int i=0; i<NN; ++i) {
		std::cout << x[i] << " ";
	}}
	std::cout << std::endl;
	std::cout <<comps/100<< " ";
	std::cout << std:: endl;
  //std::cout << qc(NN) << " ";
	//std::cout << std:: endl;

	delete[] x;
	return 0;
}
