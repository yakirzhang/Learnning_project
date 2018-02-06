#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>
using namespace std;
bool running_ = true;
void work() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  socket.setsockopt(ZMQ_RCVTIMEO, 500);
  socket.connect("tcp://127.0.0.1:5556");
  while (running_) {
    zmq::message_t msg;
    if (socket.recv(&msg)) std::cout << msg.size() << std::endl;
  }
  socket.setsockopt(ZMQ_LINGER,0);
  socket.close();
  context.close();
}
int main() {
  zmq::context_t ctx(1);
  zmq::socket_t socket(ctx, ZMQ_PUB);
  socket.bind("tcp://*:5556");
  vector<std::thread> threads;
  for (int i = 0; i < 100; i++) {
    threads.emplace_back(work);
  }
  while (running_) {
    zmq::message_t msg("hello", 5);

    sleep(2);
    socket.send(msg);
    std::cout << "send " << std::endl;
  }
  for(auto &thread:threads){
    thread.join();
  }
  ctx.close();
}