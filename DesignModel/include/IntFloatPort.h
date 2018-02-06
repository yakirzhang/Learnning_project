///"Copyright[2018] <yakirzhang>"
#pragma once
#include <port.h>

class IntFloatPort : public Port {
 public:
  class Sendingthings {
   public:
    int a_;
    float b_;
    Sendingthings(int a, float b) : a_(a), b_(b){};
  };
  IntFloatPort(int port);
  void Send(std::shared_ptr<Sendingthings> &data);
  void Parse();
  shared_ptr<Sendingthings> data_;
};
