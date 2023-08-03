/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-08-01 16:19:29
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-08-03 18:53:07
 * @FilePath: /MySTL/include/list.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef LIST_H_
#define LIST_H_

#include "allocator.h"

namespace mystl {
template <class T>
struct list_node {
    list_node* prev;
    list_node* next;
    T data;
    list_node() : prev(nullptr), next(nullptr){};
    list_node(const T& x) : prev(nullptr), next(nullptr), data(x) {}
};
template <class T>
class list {
   private:
    typedef allocator<list_node<T>> list_node_allocator;
    typedef list_node<T>* link_type;
    typedef list_node<T> node_type;
    typedef list<T> self;
    link_type _head;
    link_type _tail;
    link_type get_node() { return list_node_allocator::construct(); }
    inline link_type get_node(const T& x) {
        return list_node_allocator::construct(node_type(x));
    }

   public:
    list();
    ~list();
    list(const self& rhs);
    /// \brief 在pos前插入元素x
    /// \param pos  插入位置
    /// \param x    插入元素
    inline void insert(link_type pos, const T& x);
    inline void push_back(const T& x) { insert(_tail, x); }
    inline void push_front(const T& x) { insert(_head->next, x); }
    inline link_type begin() { return _head->next; }
    inline link_type end() { return _tail; }
    inline bool empty() { return _head->next == _tail; }
};
// template <class T>
// list<T>::list(const list::self& rhs) {
//     _head = get_node();
//     _tail = get_node();
//     _head->next = _tail;
//     _tail->prev = _head;
//     link_type cur = rhs.begin();
//     while (cur != rhs.end()) {
//         push_back(cur->data);
//         cur = cur->next;
//     }
// }

template <class T>
list<T>::list() {
    _head = get_node();
    _tail = get_node();
    _head->next = _tail;
    _tail->prev = _head;
}
template <class T>
list<T>::~list() {
    link_type cur = _head->next;
    while (cur != _tail) {
        link_type tmp = cur;
        cur = cur->next;
        list_node_allocator::deallocate(tmp);
    }
    list_node_allocator::deallocate(_head);
    list_node_allocator::deallocate(_tail);
}
template <class T>
inline void list<T>::insert(link_type pos, const T& x) {
    link_type tmp = get_node(x);
    tmp->next = pos;
    tmp->prev = pos->prev;
    pos->prev->next = tmp;
    pos->prev = tmp;
}
}  // namespace mystl

#endif  // LIST_H_