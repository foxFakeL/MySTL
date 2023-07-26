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

#include <cstddef>

void mystl::quick_sort(int* arr, int left, int right) {
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