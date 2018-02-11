//
// Created by yakirzhang on 18-2-10.
//
#include <gtest.h>
#include <Eigen/Dense>
#include <iostream>
#include <thread>
using namespace Eigen;
using namespace std;
//matrix is template that
// Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
// Scalar names type
//typedef Matrix<float, 3, 1> Vector3f;
// typedef Matrix<int, 1, 2> RowVector2i;

TEST(matrix, trans_of_matrix){
  MatrixXcf a = MatrixXcf::Random(2,2);
  cout << "Here is the matrix a\n" << a << endl;
  cout << "Here is the matrix a^T\n" << a.transpose() << endl;
  cout << "Here is the conjugate of a\n" << a.conjugate() << endl;
  cout << "Here is the matrix a^*\n" << a.adjoint() << endl;
  // !! don't do this
  a = a.transpose(); // !!! do NOT do this !!!
}
TEST(matrix, define_and_cout_matrix) {
  Eigen::MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
}
TEST(matrix1, matrix_vector_combine_Test) {
  //random value from -1 to 1
  MatrixXd m = MatrixXd::Random(3, 3);
  m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
  cout << "m =" << endl << m << endl;
  VectorXd v(3);
  //Vector can take in value through <<
  v << 1, 2, 3;
  cout << "m * v =" << endl << m * v << endl;
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
