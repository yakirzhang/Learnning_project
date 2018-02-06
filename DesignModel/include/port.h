/** PerceptIn license **/

#pragma once

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <zmq.hpp>
using namespace std;
class Port {
 public:
  class Sendingthings;
  Port(int port);

  ~Port();
  void Send();

 private:
  void SendThread();
  virtual void Parse(){};
  std::thread thread_;
  zmq::context_t context_;
  int server_port_;
  std::mutex state_mutex_;
  std::mutex data_mutex_;
  std::condition_variable cv_;
  bool running_ = true;

 protected:
  zmq::message_t msg_;
};
