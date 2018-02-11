//
// Created by yakirzhang on 18-2-7.
//
#include <gflags/gflags.h>
#include <iostream>
using namespace std;
DEFINE_bool(remote, true, "wef");
void func();
int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  func();
}
