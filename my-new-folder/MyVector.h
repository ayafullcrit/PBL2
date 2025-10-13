#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyVector {
private:
    T* data;          // mảng các phần tử kiểu T
    int size;         // số phần tử hiện có
    int capacity;     // dung lượng đã cấp phát

    void reallocate(int newCapacity) {
        // Cấp phát vùng nhớ mới
        T* newData = new T[newCapacity];

        // Sao chép dữ liệu cũ
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];

        // Giải phóng vùng nhớ cũ
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor mặc định
    MyVector(int initialCapacity = 2)
        : size(0), capacity(initialCapacity)
    {
        data = new T[capacity];
    }

    // Constructor sao chép (copy constructor)
    MyVector(const MyVector<T>& other)
        : size(other.size), capacity(other.capacity)
    {
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Destructor
    ~MyVector() {
        delete[] data;
    }

    // Thêm phần tử mới
    void push_back(const T& value) {
        if (size >= capacity)
            reallocate(capacity * 2);  // tự mở rộng khi đầy
        data[size++] = value;
    }

    // Truy cập phần tử qua chỉ số
    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    int getSize() const { return size; }

    void printAll() const {
        for (int i = 0; i < size; ++i)
            cout << i << ": " << data[i] << endl;
    }
};
