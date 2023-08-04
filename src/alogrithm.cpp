/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-27 00:54:05
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-07-27 00:56:02
 * @FilePath: /MySTL/src/alogrithm.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "alogrithm.h"

#include <cmath>
#include <cstddef>

using namespace std;

void mystl::quick_sort(int *arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left, j = right;
    int key = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= key) {
            --j;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <= key) {
            ++i;
        }
        arr[j] = arr[i];
    }
    arr[i] = key;
    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}

// 向量点乘
double operator*(vector<double> &a, vector<double> &b) {
    double result = 0;
    for (int i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
    return result;
}

// 向量乘法
vector<double> operator*(vector<double> &a, double b) {
    vector<double> result;
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] * b);
    }
    return result;
}
// 向量减法
vector<double> operator-(vector<double> &a, vector<double> &&b) {
    vector<double> result;
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] - b[i]);
    }
    return result;
}

// 向量加法
vector<double> operator+(vector<double> &a, vector<double> &b) {
    vector<double> result;
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}

// 向量除法
vector<double> operator/(vector<double> &a, double b) {
    vector<double> result;
    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] / b);
    }
    return result;
}

// 将向量正交化
vector<vector<double>> mystl::orthogonalization(vector<vector<double>> &vectors) {
    vector<vector<double>> result;
    for (int i = 0; i < vectors.size(); i++) {
        vector<double> temp = vectors[i];
        for (int j = 0; j < result.size(); j++) {
            temp = temp - (result[j] * ((vectors[i] * result[j]) / (result[j] * result[j])));
        }
        result.push_back(temp);
    }
    return result;
}

// 将向量单位化
vector<vector<double>> mystl::unitization(vector<vector<double>> &vectors) {
    vector<vector<double>> result;
    for (int i = 0; i < vectors.size(); i++) {
        result.push_back(vectors[i] / sqrt(vectors[i] * vectors[i]));
    }
    return result;
}