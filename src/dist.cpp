#include "dist.hpp"

#include <vector>

int whichPercent(int a, int b) {
  if (a > b) {
    std::swap(a, b);
  }
  if (a == b) return 100;
  return int((1 - static_cast<double>(a) / b) * 100);
}

int similarity(const std::string& s1, const std::string& s2) {
  int size1 = s1.size();
  int size2 = s2.size();
  std::vector<std::vector<int> > subAns(size1 + 1, std::vector<int>(size2 + 1));
  for (size_t i = 0; i <= size1; ++i) {
    for (size_t j = 0; j <= size2; ++j) {
      if (i == 0 || j == 0) {
        subAns[i][j] = std::max(i, j);
      } else {
        subAns[i][j] = std::min(subAns[i - 1][j], subAns[i][j - 1]) + 1;
        subAns[i][j] = std::min(subAns[i][j], 
                                    subAns[i - 1][j - 1] + int(s1[i - 1] != s2[j - 1]));
      }
    }
  }
  return whichPercent(subAns.back().back(), std::max(size1, size2));
}