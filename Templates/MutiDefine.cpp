// Yakirzhang
//用于测试模板会不会重定义，两个int型的会不会发生冲突。以及多个其他类型的使用


#include <iostream>
using namespace std;
template <class Type>
class test {
 public:
  test(Type t) : data_(t){};
  void print() { std::cout << data_ << std::endl; }

 private:
  Type data_;
};
int main() {
  test<int> t(1);
  test<int> t3(23);
  test<double> t1(1.2);
  test<float> t2(3123.4234);
  t.print();
  t1.print();
  t2.print();
  t3.print();
}