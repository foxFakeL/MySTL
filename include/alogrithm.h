#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>

namespace mystl {
void quick_sort(int* arr, int left, int right);

// 将向量正交化
std::vector<std::vector<double>> orthogonalization(std::vector<std::vector<double>>& vectors);

// 向量单位化
std::vector<std::vector<double>> unitization(std::vector<std::vector<double>>& vectors);
}  // namespace mystl

#endif  // !ALGORITHM_H