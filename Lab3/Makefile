CDate : main.cc CDate.o 
	g++ -Wall main.cc CDate.o  -o CDate

CDate.o : CDate.cc CDate.h 
	g++ -Wall -c CDate.cc -o CDate.o 

linked_list : linked_list.cc
	g++ -Wall linked_list.cc -o linked_list 

clean :
	rm -f CDate.o 
	rm -f CDate 
	rm -f linked_list 
 
