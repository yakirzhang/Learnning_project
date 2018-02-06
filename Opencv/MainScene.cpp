#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
const ostream &operator<<(ostream &os, cv::Mat &mat) {
  os << "row is : " << mat.rows << "col is : " << mat.cols << endl;
  os << "channel is : " << mat.channels() << endl;
  return os;
}
int main() {
  Mat image = imread("dota.png");
  cv::Point pt1(200,200);
  cv::Point pt2(10,100);
  cv::rectangle(image, pt1, pt2, cv::Scalar(0, 255, 0), 2);
  cv::imshow("window",image);
  waitKey(2000);


}