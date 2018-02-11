//
// Created by yakirzhang on 18-2-10.
//
#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;
int a = 10;
int &funct() { return a; }
int main() {
  auto b = funct();
  int &c=b;
  std::cout << typeid(c).name() << endl;
  b = 11;
  cout << a << endl;
}