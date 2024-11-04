#pragma once

#include <memory>

template <class T>
class FigureArray 
{
public:
    FigureArray();
    FigureArray(size_t n);
    ~FigureArray() = default;

    FigureArray(const FigureArray<T>&); // Конструктор копирования
    FigureArray(FigureArray<T>&&) noexcept; // Конструктор перемещения

    T& operator[] (size_t ind);  // Оператор доступа к элементу массива по индексу (для изменения)
    const T& operator[] (size_t ind) const; // Оператор доступа к элементу массива по индексу (для чтения)

    size_t size() const;
    void resize(size_t newSize);
    void pushBack(const T& figure); // Метод для добавления элемента в конец массива
    void erase(size_t ind); // Метод для удаления элемента по индексу
    double totalArea(); // Метод для возвращения общей площади фигур
    
private:
    size_t curSize, capacity; 
    std::unique_ptr<T[]> data; 

    void setCapacity(size_t value);  // Метод для изменения вместимости массива
    static std::unique_ptr<T[]> reallocate(std::unique_ptr<T[]> oldData, size_t oldSize, size_t newSize);

};

template <class T>
void FigureArray<T>::setCapacity(size_t value) {
    data = reallocate(std::move(data), curSize, value);
    capacity = value;
}

template <class T>
std::unique_ptr<T[]> FigureArray<T>::reallocate(std::unique_ptr<T[]> oldData, size_t oldSize, size_t newSize) {
    std::unique_ptr<T[]> data(new T[newSize]);
    // Копируем элементы из старого массива в новый
    for (size_t i = 0; i < std::min(oldSize, newSize); i++) {
        data[i] = std::move(oldData[i]);
    }
    return data;
}

template <class T>
FigureArray<T>::FigureArray() : curSize(0), capacity(0), data(nullptr) {}

template <class T>
FigureArray<T>::FigureArray(size_t n) : curSize(n), capacity(n) {
    data = std::unique_ptr<T[]>(new T[n]);
}

template <class T>
FigureArray<T>::FigureArray(const FigureArray<T>& other) : curSize(other.curSize), capacity(other.capacity) {
    data = std::unique_ptr<T[]>(new T[capacity]);
    for (size_t i = 0; i < curSize; i++) {
        data[i] = other.data[i];
    }
}

template <class T>
FigureArray<T>::FigureArray(FigureArray<T>&& other) noexcept : curSize(other.curSize), capacity(other.capacity), data(std::move(other.data)) {
    other.curSize = 0;
    other.capacity = 0;
}

template <class T>
T& FigureArray<T>::operator[] (size_t ind) {
    return data[ind];
}

template <class T>
const T& FigureArray<T>::operator[] (size_t ind) const {
    return data[ind];
}

template <class T>
size_t FigureArray<T>::size() const {
    return curSize;
}

template <class T>
void FigureArray<T>::resize(size_t newSize) {
    if (newSize > capacity) {
        setCapacity(newSize);
    }
    curSize = newSize;
}

template <class T>
void FigureArray<T>::pushBack(const T& figure) {
    resize(curSize + 1);
    data[curSize - 1] = figure;
}

template <class T>
void FigureArray<T>::erase(size_t ind) {
    // Сдвигаем элементы после удаляемого влево
    for (size_t i = ind + 1; i < curSize; i++) {
        data[i - 1] = std::move(data[i]);
    }
    if (ind < curSize) {
        curSize--;
    }
}

template <class T>
double FigureArray<T>::totalArea() {
    double res = 0.0;
    for (size_t i = 0; i != curSize; ++i) {
        if (data[i]) {
            res += static_cast<double>(*data[i]);
        }
    }
    return res;
}