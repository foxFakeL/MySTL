//
// Created by foxfake on 23-7-28.
//

#include <iostream>

using namespace std;

union Foo {
    long long i;
};

int main() {
    int* p = new int[10];
    for (int i = 0; i < 10; ++i) {
        p[i] = i;
    }
    Foo* f = reinterpret_cast<Foo*>(p);
    f->i = 100;
    for (int i = 0; i < 10; ++i) {
        cout << p[i] << " ";
    }
}