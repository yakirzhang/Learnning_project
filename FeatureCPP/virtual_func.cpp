//
// Created by yakirzhang on 18-2-10.
//

#include <iostream>

class Base {
 public:
  void func() { vfunc(); }
  virtual void vfunc() { std::cout << "hello" << std::endl; }
};
class Derived : public Base {
 public:
  void vfunc() { std::cout << "hello world" << std::endl; }
};
int main() {
  Derived d;
  d.func();
}