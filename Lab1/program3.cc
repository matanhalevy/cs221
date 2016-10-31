#include <iostream>
#include <string>
#include <fstream>
void fill_array(int start, int increment);
int a[10];

int main(void){
	int start_num;
	int incre_num;
	std::cout <<"Enter starting number: " << std::endl;
	std:: cin >> start_num;
	std::cout <<"Enter increment: " << std::endl;
	std:: cin >> incre_num;
	fill_array(start_num, incre_num); 
	std::cout << "These are the numbers of the array: " << std::endl;
	for (int i = 0; i < 10; i++){
	std::cout << a[i] << " " << std::endl;}
	return 0;
}
	
void fill_array(int start, int increment){
	for(int i = 0; i < 10; i++){ 
		a[i] = start +(increment*i);
	}
}

	
	