#include <unistd.h>
#include <iostream>
#include <thread>
#include <zmq.hpp>
bool running_ = true;
void work(zmq::context_t *context) {
  zmq::socket_t socket(*context, ZMQ_SUB);
  socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  socket.setsockopt(ZMQ_RCVTIMEO, 500);
  socket.connect("inproc://whatifsendtwice");
  while (running_) {
    zmq::message_t msg;
    if (socket.recv(&msg)) std::cout << msg.size() << std::endl;
  }
}
int main() {
  zmq::context_t ctx(1);
  zmq::socket_t socket(ctx, ZMQ_PUB);
  socket.bind("inproc://whatifsendtwice");
  std::thread thread_(work, &ctx);
  zmq::message_t msg("hello", 5);
  while (running_) {
    sleep(2);
    socket.send(msg);
    std::cout << "send " << std::endl;
  }
  thread_.join();
}