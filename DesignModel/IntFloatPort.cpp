#include <IntFloatPort.h>

IntFloatPort::IntFloatPort(int port) : Port(port) {}

void IntFloatPort::Send(std::shared_ptr<Sendingthings> &data) {
  data_ = data;
  Port::Send();
}
void IntFloatPort::Parse() {
  zmq::message_t msg(sizeof(int) + sizeof(float));
  char buff[10];
  snprintf(buff, 10, "%d%f", data_->a_, data_->b_);
  memcpy(msg.data(), buff, 10);
  Port::msg_.copy(&msg);
  Port::Send();
}