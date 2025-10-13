template <typename T>
void reallocArray(T**& arr, int& oldSize, int newSize) {
    T** temp = new T*[newSize];

    // Sao chép con trỏ cũ
    for (int i = 0; i < oldSize; ++i)
        temp[i] = arr[i];

    // Khởi tạo vùng mới (nếu cần)
    for (int i = oldSize; i < newSize; ++i)
        temp[i] = nullptr;

    // Giải phóng mảng con trỏ cũ (chỉ mảng, không xóa đối tượng)
    delete[] arr;

    arr = temp;
    oldSize = newSize;
}