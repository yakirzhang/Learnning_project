#include "pid.h"
#include <algorithm>

class PID::Impl {
 public:
  explicit Impl(const Parameters &params)
      : kp_(params.kp),
        ki_(params.ki),
        kd_(params.kd),
        min_output_(params.min_output),
        max_output_(params.max_output),
        min_input_offset_(params.min_input_offset),
        max_output_ramp_rate_(params.max_output_ramp_rate),
        is_first_run_(true),
        is_for_rotating_(params.is_for_rotating),
        prev_error_(0),
        error_sum_(0),
        prev_output_(0.0) {}

 private:
  double kp_, ki_, kd_;
  double min_output_, max_output_;
  double min_input_offset_;
  double max_output_ramp_rate_;
  bool is_first_run_;
  bool is_for_rotating_;
  double prev_error_;
  double error_sum_;
  double prev_output_;
  double CalculateOutput(double set_point, double actual_val, double dt);
  double ProcessOutput(double raw_output);
  friend PID;
};
PID::Parameters::Parameters()
    : kp(0.3),
      ki(0),
      kd(0.01),
      min_output(0.03),
      max_output(0.25),
      min_input_offset(0.01),
      max_output_ramp_rate(0.05),
      is_for_rotating(true) {}

PID::Parameters::~Parameters() = default;

PID::PID(const Parameters &params) : impl_(std::make_shared<Impl>(params)) {}

PID::PID(PID &&other) {
  impl_ = other.impl_;
  other.impl_.reset();
}

void PID::SetPID(double kp, double ki, double kd) {
  impl_->kp_ = kp;
  impl_->ki_ = ki;
  impl_->kd_ = kd;
}

void PID::SetOutputLimits(double min, double max) {
  impl_->min_output_ = min;
  impl_->max_output_ = max;
}

void PID::SetOutputMin(double min) { impl_->min_output_ = min; }

void PID::SetOutputMax(double max) { impl_->max_output_ = max; }

void PID::SetPreviousOutput(double prev_output) {
  impl_->prev_output_ = prev_output;
}

double PID::GetOutput(double set_point, double actual_val, double dt) {
  return impl_->CalculateOutput(set_point, actual_val, dt);
}

double PID::Impl::CalculateOutput(double set_point, double actual_val,
                                  double dt) {
  double error = set_point - actual_val;
  double delta_error = (error - prev_error_) / dt;
  if (is_first_run_ || dt == 0) {
    delta_error = 0;
    is_first_run_ = false;
  }
  prev_error_ = error;
  error_sum_ += error;
  double raw_output = kp_ * error + ki_ * error_sum_ + kd_ * delta_error;

  return ProcessOutput(raw_output);
}

double PID::Impl::ProcessOutput(double raw_output) {
  double output = raw_output;
  // clamp
  output = output > max_output_ ? max_output_ : output;
  output = output < -max_output_ ? -max_output_ : output;

  if (fabs(output) < min_output_) {
    if (output > 0) {
      output = min_output_;
    } else {
      output = -min_output_;
    }
  }


  // constant acceleration
  if (fabs(output - prev_output_) > max_output_ramp_rate_) {
    output = output > prev_output_ ? prev_output_ + max_output_ramp_rate_
                                   : prev_output_ - max_output_ramp_rate_;
  }
  prev_output_ = output;

  return output;
}

void PID::Reset() {
  impl_->error_sum_ = 0;
  impl_->prev_output_ = 0;
  impl_->prev_error_ = 0;
  impl_->is_first_run_ = true;
}