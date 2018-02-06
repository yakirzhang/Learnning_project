#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <zmq.hpp>
using namespace std;
bool running = true;
void subs(zmq::context_t *ctx) {
  zmq::socket_t socket(*ctx, ZMQ_SUB);
  socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  socket.setsockopt(ZMQ_RCVTIMEO, 500);
  socket.setsockopt(ZMQ_RCVHWM, 1);
  socket.connect("tcp://127.0.0.1:5556");
  sleep(3);
  while (running) {
    zmq::message_t msg;
    if (socket.recv(&msg)) {
      char *databegin = reinterpret_cast<char *>(msg.data());
      string s;
      s.insert(s.begin(), databegin, databegin + msg.size());
      std::cout << "recv : " << s << std::endl;
    }
  }
  socket.setsockopt(ZMQ_LINGER, 0);
  socket.close();
}
int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_PUB);
  socket.setsockopt(ZMQ_SNDHWM, 1);
  socket.bind("tcp://*:5556");
  char buff[20] = {0};
  vector<std::thread> threads;
  for (int i = 0; i < 5; i++) {
    threads.emplace_back(subs, &context);
  }
  for (int i = 0; i < 1000; i++) {
    snprintf(buff, sizeof(buff), "package %d", i);
    zmq::message_t msg(buff, sizeof(buff));
    socket.send(msg);
    std::cout << "send one" << i << std::endl;
  }

  for (auto &thread : threads) {
    if (thread.joinable()) thread.join();
  }
  context.close();
}