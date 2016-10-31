
#include <iostream>

int main() {
  int x = 5;
  int y = 15;
  int* p1;
  int* p2;

  p1 = &x;  // x=5   y= 15  p1 = address x  p2 = unassigned.
  std::cout << "p1 = &x: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;
  
  p2 = &y; // x=5   y= 15  p1 = address x  p2 = address y
  std::cout << "p2 = &y: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;
  
  *p1 = 6; // x=6   y= 15  p1 = address of x  p2 = address y
  std::cout << "*p1 = 6: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;

  *p1 = *p2; // x=15   y= 15  p1 = address of x  p2 = address y
  std::cout << "*p1 = *p2: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;
  
  p2 = p1;  // x=15   y= 15  p1 = address of x  p2 = address x
  std::cout << "p1 = p2: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;

  *p1 = *p2+10; // x=25   y= 15  p1 = address of x  p2 = address x
  std::cout << "*p1 = *p2+10: " << std::endl;
  std::cout << "x  = " << x << std::endl;
  std::cout << "y  = " << y << std::endl;
  std::cout << "p1  = " << p1 << std::endl;
  std::cout << "p2  = " << p2 << std::endl;

  return 0;
}
