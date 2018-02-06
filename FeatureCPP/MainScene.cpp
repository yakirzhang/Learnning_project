#include <iostream>
using namespace std;
int main() {
  int i = 0;
  while (cin >> i) {
    string s = to_string(i);
    cout << s << endl;
  }
}