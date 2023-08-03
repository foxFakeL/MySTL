#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <cstddef>

#include "alloc.h"
#include "config.h"
namespace mystl {
template <class T>
class allocator {
   public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

   public:
    static T* allocate();
    static T* allocate(size_type n);
    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_type n);
    static T* construct();
    static T* construct(T&& value);
    static void destroy(T* ptr);
    static void destroy(T* first, T* last);
};

template <class T>
T* allocator<T>::allocate() {
    if (USING_ALLOC_H) {
        return static_cast<T*>(alloc::allocate(sizeof(T)));
    } else {
        return static_cast<T*>(::operator new(sizeof(T)));
    }
}

template <class T>
T* allocator<T>::allocate(size_type n) {
    if (USING_ALLOC_H) {
        if (n == 0) return nullptr;
        return static_cast<T*>(alloc::allocate(sizeof(T) * n));
    } else {
        if (n == 0) return nullptr;
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }
}

template <class T>
void allocator<T>::deallocate(T* ptr) {
    if (USING_ALLOC_H) {
        alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
    } else {
        ::operator delete(static_cast<void*>(ptr));
    }
}
template <class T>
void allocator<T>::deallocate(T* ptr, size_type n) {
    if (USING_ALLOC_H) {
        if (n == 0) return;
        alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
    } else {
        if (n == 0) return;
        ::operator delete(static_cast<void*>(ptr));
    }
}

template <class T>
T* allocator<T>::construct() {
    if (USING_ALLOC_H) {
        void* ptr = alloc::allocate(sizeof(T));
        auto t = new (ptr) T();
        return new (ptr) T();
    } else {
        T* ptr = static_cast<T*>(::operator new(sizeof(T)));
        new (ptr) T();
        return ptr;
    }
}

template <class T>
T* allocator<T>::construct(T&& value) {
    if (USING_ALLOC_H) {
        void* ptr = alloc::allocate(sizeof(T));
        return new (ptr) T(std::forward<T>(value));
    } else {
        T* ptr = static_cast<T*>(::operator new(sizeof(T)));
        new (ptr) T(std::move(value));
        return ptr;
    }
}
template <class T>
void allocator<T>::destroy(T* ptr) {
    if (USING_ALLOC_H) {
        ptr->~T();
        alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
    } else {
        ptr->~T();
        ::operator delete(static_cast<void*>(ptr));
    }
}
template <class T>
void allocator<T>::destroy(T* first, T* last) {
    if (USING_ALLOC_H) {
        for (; first != last; ++first) {
            first->~T();
            alloc::deallocate(static_cast<void*>(first), sizeof(T));
        }
    } else {
        for (; first != last; ++first) {
            first->~T();
        }
        ::operator delete(static_cast<void*>(first));
    }
}
}  // namespace mystl
#endif