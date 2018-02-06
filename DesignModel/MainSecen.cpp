#include <IntFloatPort.h>
#include <iostream>
#include <string>
#include <memory>
using namespace std;
int main() {
  IntFloatPort port(5557);

  int a=0;
  float b=0;
  while(cin>>a>>b){
    auto s = std::make_shared<IntFloatPort::Sendingthings>(a,b);
    port.Send(s);
  }
}