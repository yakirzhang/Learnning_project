///"Copyright[2018] <yakirzhang>"
#include <port.h>

Port::Port(int port)
    : context_(zmq::context_t(1)), server_port_(port), running_(true) {
  thread_ = std::thread(&Port::SendThread, this);
}
void Port::Send() {
  if (data_mutex_.try_lock()) {
    cv_.notify_one();
    data_mutex_.unlock();
  }
}

void Port::SendThread() {
  zmq::socket_t socket(context_, ZMQ_PUB);
  char address[30] = {0};
  snprintf(address, sizeof(address), "tcp://*:%d", server_port_);
  socket.bind(address);
  while (true) {
    {
      std::lock_guard<std::mutex> lck(state_mutex_);
      if (!running_) {
        break;
      }
    }
    std::unique_lock<std::mutex> lck(data_mutex_);
    if (cv_.wait_for(lck, std::chrono::milliseconds(1000)) ==
        std::cv_status::timeout)
      continue;
    Parse();
    char *databegin = reinterpret_cast<char *>(msg_.data());
    string tmp;
    tmp.insert(tmp.begin(), databegin, databegin + msg_.size());
    socket.send(msg_);
    std::cout << "send " << tmp << std::endl;
  }
}

Port::~Port() {
  {
    std::lock_guard<std::mutex> lck(state_mutex_);
    running_ = false;
  }
  if (thread_.joinable()) thread_.join();
  { context_.close(); }
}
