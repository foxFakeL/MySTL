/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-26 23:34:45
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-07-27 01:03:04
 * @FilePath: /MySTL/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "alloc.h"
#include "alogrithm.h"
using namespace std;
using namespace mystl;

int main() {
    // 测试内存池
    // cout << "test alloc" << endl;
    // cout << "test alloc::allocate" << endl;
    // int* p = static_cast<int*>(alloc::allocate(sizeof(int) * 10));
    // for (int i = 0; i < 10; ++i) {
    //     p[i] = rand() % 100;
    // }
    // quick_sort(p, 0, 9);
    // for (int i = 0; i < 10; ++i) {
    //     cout << p[i] << " ";
    // }
    // cout << endl;
    // cout << "test alloc::deallocate" << endl;
    // alloc::deallocate(p, sizeof(int) * 10);
    // cout << "test alloc::reallocate" << endl;
    // p = static_cast<int*>(
    //     alloc::reallocate(p, sizeof(int) * 10, sizeof(int) * 20));
    // for (int i = 0; i < 20; ++i) {
    //     cout << p[i] << " ";
    // }
    // cout << endl;
    // alloc::deallocate(p, sizeof(int) * 20);
    // 测试内存池性能
    cout << "test alloc performance" << endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 10000000; ++i) {
        int* p = static_cast<int*>(alloc::allocate(sizeof(int) * 10));
        alloc::deallocate(p, sizeof(int) * 10);
    }
    end = clock();
    end = clock();
    cout << "alloc time: " << end - start << endl;
    // 测试malloc
    cout << "test malloc" << endl;
    start = clock();
    for (int i = 0; i < 10000000; ++i) {
        int* p = static_cast<int*>(malloc(sizeof(int) * 10));
        free(p);
    }
    end = clock();
    cout << "malloc time: " << end - start << endl;
}