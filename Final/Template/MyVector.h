#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyVector
{
private:
    T *data;      // mảng các phần tử kiểu T
    int size;     // số phần tử hiện có
    int capacity; // dung lượng đã cấp phát

    void clear()
    {
        // Giải phóng tất cả các đối tượng được trỏ đến
        for (int i = 0; i < size; ++i)
        {
            delete data[i];
        }
        // Đặt lại kích thước về 0
        size = 0;
    }
    void reallocate(size_t new_capacity)
    {
        if (new_capacity <= capacity)
            return;

        T *new_data = static_cast<T *>(::operator new(new_capacity * sizeof(T)));
        size_t i = 0;

        try
        {
            // Di chuyển/copy các phần tử cũ sang vùng nhớ mới
            for (; i < size; ++i)
            {
                new (new_data + i) T(std::move_if_noexcept(data[i]));
            }
        }
        catch (...)
        {
            // Dọn dẹp những phần tử đã được tạo
            for (size_t j = 0; j < i; ++j)
            {
                new_data[j].~T();
            }
            ::operator delete(new_data);
            throw; // Re-throw exception
        }

        // Dọn dẹp vùng nhớ cũ
        for (size_t j = 0; j < size; ++j)
        {
            data[j].~T();
        }
        ::operator delete(data);

        data = new_data;
        capacity = new_capacity;
    }
    // void reallocate(int newCapacity)
    // {
    //     // Cấp phát vùng nhớ mới
    //     T *newData = new T[newCapacity];

    //     // Sao chép dữ liệu cũ
    //     for (int i = 0; i < size; ++i)
    //         newData[i] = data[i];
    //     // Giải phóng vùng nhớ cũ
    //     delete[] data;
    //     data = newData;
    //     capacity = newCapacity;
    // }

public:
    // Constructor mặc định
    MyVector(int initialCapacity = 20)
        : size(0), capacity(initialCapacity)
    {
        data = new T[capacity];
    }

    // Constructor sao chép (copy constructor)
    MyVector(const MyVector<T> &other)
        : size(other.size), capacity(other.capacity)
    {
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Destructor
    ~MyVector()
    {
        delete[] data;
    }

    // Thêm phần tử mới
    // void push_back(const T &value)
    // {
    //     if (size >= capacity)
    //         reallocate(capacity * 2); // tự mở rộng khi đầy
    //     data[size++] = value;
    // }
    void push_back(const T &value)
    {
        // Đảm bảo có đủ capacity
        if (size >= capacity)
        {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            reallocate(new_capacity);
        }

        // Placement new với copy constructor
        new (data + size) T(value);
        ++size;
    }

    // Phiên bản move (T&&)
    void push_back(T &&value)
    {
        if (size >= capacity)
        {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            reallocate(new_capacity);
        }

        // Placement new với move constructor
        new (data + size) T(std::move(value));
        ++size;
    }
    void removeAt(int index)
    {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");

        // Giải phóng đối tượng tại vị trí index
        // delete data[index];

        // Dịch các phần tử phía sau sang trái
        for (int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];

        // Giảm size và dọn con trỏ cuối
        --size;
    }
    void pop_back()
    {
        if (size == 0)
        {
            throw out_of_range("Vector is empty");
        }
        removeAt(size - 1);
    }
    // Truy cập phần tử qua chỉ số
    T &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }
    MyVector<T> &operator=(const MyVector<T> &other)
    {
        if (this == &other) // kiểm tra tự gán
            return *this;

        // Giải phóng bộ nhớ cũ
        delete[] data;

        // Sao chép dữ liệu từ other
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];

        return *this;
    }
    int getSize() const { return size; }

    void printAll() const
    {
        for (int i = 0; i < size; ++i)
            cout << i << ": " << data[i] << endl;
    }
};
