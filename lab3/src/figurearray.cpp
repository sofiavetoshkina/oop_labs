#include "figure.h"
#include "figurearray.h"

void FigureArray::setCapacity(size_t value) {
    data = reallocate(data, curSize, value);
    capacity = value;
}

Figure** FigureArray::reallocate(Figure** oldData, size_t oldSize, size_t newSize) {
    Figure** data = new Figure* [newSize];
    // Копируем элементы из старого массива в новый
    for (size_t i = 0; i < std::min(oldSize, newSize); i++) {
        data[i] = oldData[i];
    }
    // Освобождаем память, занятую старым массивом, если он не был nullptr
    if (oldData != nullptr) {
        delete [] oldData;
    }
    return data;
}

FigureArray::FigureArray() : curSize(0), capacity(0), data(nullptr) {}

FigureArray::FigureArray(size_t n) : curSize(n), capacity(n) {
    data = reallocate(nullptr, 0, n);
}

FigureArray::~FigureArray() {
    // Освобождаем память, занятую массивом указателей
    delete [] data;
}

FigureArray::FigureArray(const FigureArray& other) {
    data = reallocate(nullptr, 0, other.size());
    for (size_t i = 0; i < other.size(); i++) {
        data[i] = other.data[i];
    }
    curSize = other.size();
    capacity = other.capacity;
}

FigureArray::FigureArray(FigureArray&& other) noexcept {
    data = other.data;
    curSize = other.size();
    capacity = other.capacity;
    other.data = nullptr;
}

Figure* & FigureArray::operator[] (size_t ind) {
    return data[ind];
}

Figure* & FigureArray::operator[] (size_t ind) const {
    return data[ind];
}

size_t FigureArray::size() const {
    return curSize;
}

void FigureArray::resize(size_t newSize) {
    if (newSize > capacity) {
        setCapacity(newSize);
    }
    curSize = newSize;
}

void FigureArray::pushBack(Figure* figure) {
    resize(curSize + 1);
    (*this)[curSize - 1] = figure;
}

void FigureArray::erase(size_t ind) {
    // Сдвигаем элементы после удаляемого влево
    for (size_t i = ind + 1; i < curSize; i++) {
        data[i - 1] = data[i];
    }
    if (ind < curSize) {
        curSize--;
    }
}

double FigureArray::totalArea() {
    double res = 0.0;
    for (size_t i = 0; i != curSize; ++i) {
        if (data[i] != nullptr)
            res += (double)*data[i];
    }
    return res;
}