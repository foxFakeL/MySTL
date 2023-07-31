/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-26 23:36:24
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-07-27 00:33:18
 * @FilePath: /MySTL/include/alloc.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef ALLOC_H
#define ALLOC_H
#include <cstddef>
namespace mystl {
class alloc {
   private:
    enum { ALIGN = 8 };
    enum { MAX_BYTES = 128 };
    enum { NFREELISTS = MAX_BYTES / ALIGN };

   private:
    // 为了节省空间，不单独使用类似于list_node的节点分别储存内容和下一个节点的指针，
    // 而是将下一个节点的指针和内容放在同一个空间，下一个节点的指针在当前内存块的最前面
    // 这样就可以通过指针的类型转换来获取内容和下一个节点的指针
    // 但是这样会导致内存对齐的问题，所以需要将内存块的大小设置为8的倍数
    union FreeListNode {
        union FreeListNode* free_list_link;  // 指向下一个节点
    };

    typedef FreeListNode FreeList;

   private:
    static FreeList* volatile free_list[NFREELISTS];

   private:
    static char* start_free;
    static char* end_free;
    static size_t heap_size;  // 内存池大小

   private:
    static inline size_t ROUND_UP(size_t bytes) {
        return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
    }

    /**
     * @brief
     * 根据申请的空间大小，找到对应的free_list下标
     * @param bytes 申请的空间大小
     * @return size_t 下标
     */
    static inline size_t FREELIST_INDEX(size_t bytes) {
        return ((bytes + ALIGN - 1) / ALIGN - 1);
    }

    /**
     * @brief
     * 从内存池中取空间给free_list使用，当下标为n的free_list为空时，调用该函数
     * @param n 申请的空间大小
     */
    static void* refill(size_t n);

    /**
     * @brief 从内存池中取空间给free_list使用
     * @param size 申请的空间大小
     * @param nobjs 申请的空间个数
     */
    static char* chunk_alloc(size_t size, int& nobjs);

   public:
    /**
     * @brief 申请空间
     * @param n 申请的空间大小
     */
    static void* allocate(size_t n);
    /**
     * @brief 释放空间
     * @param p 释放的空间指针
     * @param n 释放的空间大小
     */
    static void deallocate(void* p, size_t n);
    /**
     * @brief 重新申请空间
     * @param p 旧空间指针
     * @param old_sz 旧空间大小
     * @param new_sz 新空间大小
     */
    static void* reallocate(void* p, size_t old_sz, size_t new_sz);
};
}  // namespace mystl

#endif  // ALLOC_H