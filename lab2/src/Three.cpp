#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include "Three.h"

bool Three::isTernary(const unsigned char& symbol){
    return (symbol >= '0' && symbol <= '2');
}

Three::Three() : _size(0), _array{nullptr} {}

Three::Three(unsigned int number){
    _size = 0;
    unsigned int tmp = number;
    do{
        tmp /= 3;
        _size++;
    } while (tmp != 0);
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i){
        _array[i] = (number % 3) + '0'; // цифры в виде символов
        number /= 3;
    }
}

Three::Three(const std::initializer_list<unsigned char>& t){
    _size = t.size();
    _array = new unsigned char[_size];
    size_t i = _size - 1;
    for (unsigned char tmp : t){
        if (!isTernary(tmp))
            throw std::invalid_argument("number is not ternary.");
        _array[i--] = tmp;
    }
}

Three::Three(const std::string& t){
    _size = t.size();
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++){
        if (!isTernary(t[i]))
            throw std::invalid_argument("number is not ternary.");
        _array[_size - 1 - i] = t[i];
    }
}

Three::Three(const Three& other){
    _size = other._size;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++){
        _array[i] = other._array[i];
    }
}

Three::Three(Three&& other) noexcept{
    _size = other._size;
    _array = other._array;
    other._size = 0;
    other._array = nullptr;
}

Three Three::add(const Three& other) const{
    size_t max_size = std::max(_size, other._size);
    unsigned char* result_array = new unsigned char[max_size + 1];
    size_t i{0};
    int transfer_num{0}; // перенос
    while (i < max_size || transfer_num > 0){
        int digit1{0}, digit2{0};
        if (i <_size){
            digit1 = _array[i] - '0';
        }
        if (i < other._size){
            digit2 = other._array[i] - '0';
        }
        int sum = digit1 + digit2 + transfer_num;
        result_array[i] = (sum % 3) + '0';
        transfer_num = sum / 3;
        ++i;
    }

    Three result;
    result._array = result_array;
    result._size = i;
    return result;
}

Three Three::subtract(const Three& other) const{
    if (less_than(other))
        throw std::range_error("number_1 - number_2 is less than 0.");
    size_t max_size = std::max(_size, other._size);
    unsigned char* result_array = new unsigned char[max_size];
    size_t i{0};
    int borrow{0}; // заём
    while (i < max_size){
        int digit1{0}, digit2{0};
        if (i < _size){
            digit1 = _array[i] - '0';
        }
        if (i < other._size){
            digit2 = other._array[i] - '0';
        }
        int diff = digit1 - digit2 - borrow;
        if (diff < 0){
            diff += 3;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result_array[i] = diff + '0';
        ++i;
    }

    while (i > 0 && result_array[i - 1] == '0'){
        --i;
    }
    if (i == 0){
        ++i;
    }

    Three result;
    result._size = i;
    result._array = result_array;
    return result;
}

bool Three::equals(const Three& other) const{
    if (_size != other._size)
        return false;
    for (size_t i = 0; i < _size; ++i){
        if (_array[i] != other._array[i])
            return false;
    }
    return true;
}

bool Three::less_than(const Three& other) const{
    if (_size < other._size)
        return true;
    else if (_size > other._size)
        return false;
    if (_size == 0)
        return false;
    size_t i{0};
    while (i < _size && _array[i] == other._array[i])
        ++i;
    if (i == _size)
        return false;
    return _array[i] < other._array[i];
}

bool Three::greater_than(const Three& other) const{
    if (_size > other._size)
        return true;
    else if (_size < other._size)
        return false;
    if (_size == 0)
        return false;
    int i = _size - 1;
    while (i >= 0 && _array[i] == other._array[i])
        --i;
    if (i == -1)
        return false;
    return _array[i] > other._array[i];
}

bool Three::operator >(const Three& other) const{
    return greater_than(other);
}

bool Three::operator >=(const Three& other) const{
    return greater_than(other) || equals(other);
}

bool Three::operator <(const Three& other) const{
    return less_than(other);
}

bool Three::operator <=(const Three& other) const{
    return less_than(other) || equals(other);
}

Three Three::operator +(const Three& other) const{
    return add(other);
}

Three Three::operator -(const Three& other) const{
    return subtract(other);
}

Three& Three::operator =(const Three& other){
    if (this != &other){
        delete[] _array;
        _array = new unsigned char[_size];
        for (size_t i = 0; i < _size; i++){
            _array[i] = other._array[i];
        }
    }
    return *this;
}

Three& Three::operator =(Three&& other) noexcept{
    if (this != &other){
        delete[] _array;
        _size = other._size;
        _array = other._array;
        other._size = 0;
        other._array = nullptr;
    }
    return *this;
}

std::ostream& Three::print(std::ostream& os){
    for (size_t i = _size; i > 0 ; --i){
        os << _array[i - 1];
    }
    return os;
}

Three::~Three() noexcept{
    delete[] _array;
}