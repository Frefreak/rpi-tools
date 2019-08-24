#include <iostream>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() {
  std::vector<int> x(1000), y(1000);
  for (int i = 0; i < 1000; i++) {
    x.at(i) = i;
    y.at(i) = (i/10 % 2)? 1: 0;
  }
  plt::plot(x, y, "r-");
  plt::save("./test.png");
}
