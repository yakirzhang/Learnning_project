//
// Created by yakirzhang on 18-2-7.
//
#include <iostream>
#include <gflags/gflags_declare.h>

DECLARE_bool(remote);
void func() {
  if (FLAGS_remote) std::cout << "hello world" << std::endl;
}