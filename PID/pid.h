/** PerceptIn license **/
#include <memory>
#pragma once

class PID {
 public:
  struct Parameters {
    /// PID parameter
    double kp, ki, kd;
    double min_output, max_output;
    double min_input_offset;
    double max_output_ramp_rate;
    double prev_output;
    bool is_for_rotating;
    Parameters();
    ~Parameters();
  };
  PID(const Parameters &params);
  PID(const PID &other) = delete;
  PID &operator=(const PID &other) = delete;
  PID(PID &&other);
  void SetPID(double kp, double ki, double kd);
  void SetOutputLimits(double min, double max);
  void SetPreviousOutput(double prev_output);
  double GetOutput(double set_point, double actual_val, double dt);
  void SetOutputMin(double min);
  void SetOutputMax(double max);
  void Reset();

 private:
  class Impl;
  std::shared_ptr<Impl> impl_;
};