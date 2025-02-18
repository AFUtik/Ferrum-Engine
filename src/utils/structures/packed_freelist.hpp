#ifndef PACKED_FREELIST_HPP
#define PACKED_FREELIST_HPP

#include <cstdint>

template<typename T>
class packed_freelist {
private:
    T* data;
    int* next;

    uint32_t free_head;
    uint32_t capacity;
public:
    packed_freelist(const size_t &n) : data(new T[n]), next(new int[n]), free_head(0) {
        for (int i = 0; i < n - 1; ++i) next[i] = i + 1;
        
        next[n - 1] = -1;
    }

    ~packed_freelist() {
        delete[] data;
        delete[] next;
    }

    int allocate(const T& object) {
        if (free_head == -1) return -1;

        int index = free_head;
        free_head = next[free_head];
        data[index] = object;
        return index;
    }

    void deallocate(int index) {
        next[index] = free_head;
        free_head = index;
    }
    
    void resize(const size_t &new_capacity) {
        if (new_capacity <= capacity) return;

        T* new_data = new T[new_capacity];
        int* new_next = new int[new_capacity];

        for (int i = 0; i < capacity; i++) {
            new_data[i] = data[i];
            new_next[i] = next[i];
        }

        for(int i = capacity; i < new_capacity - 1; i++) new_next[i] = i + 1;
        
        new_next[new_capacity - 1] = -1;

        delete[] data;
        delete[] next;

        data = new_data;
        next = new_next;
        free_head = capacity;
        capacity = new_capacity;
    }

    T& operator[](const size_t &index) {
        return data[index];
    }

    const T& operator[](const size_t &index) const {
        return data[index];
    }
};

#endif