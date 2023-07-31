/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-27 00:04:55
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-07-27 00:34:47
 * @FilePath: /MySTL/src/alloc.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "alloc.h"
#include <cstdlib>
using namespace mystl;
using namespace std;

char* alloc::start_free = nullptr;
char* alloc::end_free = nullptr;
size_t alloc::heap_size = 0;

alloc::FreeList* volatile alloc::free_list[alloc::NFREELISTS] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

void* alloc::allocate(size_t n) {
    if (n > static_cast<size_t>(MAX_BYTES)) {
        return malloc(n);
    }

    FreeList* volatile* my_free_list =
        free_list + FREELIST_INDEX(n);  // 找到对应的free_list

    FreeList* result = *my_free_list;
    if (result == nullptr) {
        void* r = refill(ROUND_UP(n));
        return r;
    }

    *my_free_list = result->free_list_link;
    return result;
}

void alloc::deallocate(void* p, size_t n) {
    if (n > static_cast<size_t>(MAX_BYTES)) {
        free(p);
        return;
    }

    FreeList* volatile* my_free_list =
        free_list + FREELIST_INDEX(n);  // 找到对应的free_list

    FreeList* q = static_cast<FreeList*>(p);
    // 回收内存,将内存插入到free_list的头部，然后将free_list指向新的头部
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

void* alloc::reallocate(void* p, size_t old_sz, size_t new_sz) {
    deallocate(p, old_sz);
    p = allocate(new_sz);
    return p;
}

char* alloc::chunk_alloc(size_t size, int& nobjs) {
    // size 一定是8的倍数!!!!!!这是前面的代码保证的
    char* result = nullptr;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;

    if (bytes_left >= total_bytes) {  // 内存池剩余空间足够
        result = start_free;
        start_free += total_bytes;
        return result;
    } else if (bytes_left >= size) {  // 只够分配一个或者多个
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    } else {  // 内存池剩余空间不足以分配一个
        size_t bytes_to_get =
            2 * total_bytes + ROUND_UP(heap_size >> 4);  // 申请两倍的空间
        // TODO 为什么要加上ROUND_UP(heap_size >> 4)
        if (bytes_left > 0) {  // 将内存池剩余空间分配给free_list，bytes_left一定是8的倍数
            FreeList* volatile* my_free_list =
                free_list + FREELIST_INDEX(bytes_left);
            reinterpret_cast<FreeList*>(start_free)->free_list_link =
                *my_free_list;
            *my_free_list = reinterpret_cast<FreeList*>(start_free);
        }

        start_free = static_cast<char*>(malloc(bytes_to_get));
        if (start_free == nullptr) {    // 当系统中没有内存可用时,从free_list中找到合适的内存块
            FreeList* volatile* my_free_list = nullptr;
            FreeList* p = nullptr;
            for (int i = size; i <= MAX_BYTES; i += ALIGN) {    // 从free_list中找到合适的内存块
                my_free_list = free_list + FREELIST_INDEX(i);   // i 一定是8的倍数，所以不用ROUND_UP
                p = *my_free_list;
                if (p != nullptr) {
                    *my_free_list = p->free_list_link;  // 将当前内存块从free_list中移除
                    // 用当前内存块更新start_free和end_free
                    start_free = reinterpret_cast<char*>(p);
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
            end_free = nullptr;
            start_free =
                static_cast<char*>(malloc(bytes_to_get));  // 内存池已经用完了，再尝试从系统中申请内存
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

void* alloc::refill(size_t n) {
    int nobjs = 20;
    char* chunk = chunk_alloc(n, nobjs);    // 从内存池中获取内存
    FreeList* volatile* my_free_list = nullptr;
    FreeList* result = nullptr;
    FreeList* current_obj = nullptr;
    FreeList* next_obj = nullptr;

    if (nobjs == 1) {
        return chunk;
    }

    my_free_list = free_list + FREELIST_INDEX(n);
    result = reinterpret_cast<FreeList*>(chunk);
    *my_free_list = next_obj = reinterpret_cast<FreeList*>(chunk + n);

    for (int i = 1;; ++i) {
        current_obj = next_obj;
        next_obj =
            reinterpret_cast<FreeList*>(reinterpret_cast<char*>(next_obj) + n);
        if (nobjs - 1 == i) {
            current_obj->free_list_link = nullptr;
            break;
        } else {
            current_obj->free_list_link = next_obj;
        }
    }

    return result;
}