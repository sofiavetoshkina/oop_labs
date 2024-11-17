#pragma once

#include <memory>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <type_traits>
#include <cassert>

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class Queue {
public:
    Queue(const Allocator& alloc = Allocator())
        : _head(nullptr), _tail(nullptr), _size(0), _allocator(alloc) {}

    ~Queue() = default;

    void push(const T& value) {
        auto new_node = std::make_unique<Node>(value, _allocator);
        if (_tail) {
            _tail->next = std::move(new_node);
            _tail = _tail->next.get();
        } else {
            _head = std::move(new_node);
            _tail = _head.get();
        }
        ++_size;
    }

    void push(T&& value) {
        auto new_node = std::make_unique<Node>(std::move(value), _allocator);
        if (_tail) {
            _tail->next = std::move(new_node);
            _tail = _tail->next.get();
        } else {
            _head = std::move(new_node);
            _tail = _head.get();
        }
        ++_size;
    }

    T pop() {
        if (!_head) {
            throw std::out_of_range("Очередь пуста.");
        }
        T value = std::move(_head->value);
        _head = std::move(_head->next);
        if (!_head) {
            _tail = nullptr;
        }
        --_size;
        return value;
    }

    size_t size() const noexcept {
        return _size;
    }

    bool empty() const noexcept {
        return _size == 0;
    }

    class Iterator;
    Iterator begin() { return Iterator(_head.get()); }
    Iterator end() { return Iterator(nullptr); }

private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;

        Node(const T& val, const Allocator& alloc)
            : value(val), next(nullptr) {}

        Node(T&& val, const Allocator& alloc)
            : value(std::move(val)), next(nullptr) {}
    };

    std::unique_ptr<Node> _head;
    Node* _tail;
    size_t _size;
    Allocator _allocator;
};

// Итератор
template<typename T, typename Allocator>
class Queue<T, Allocator>::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node* node) : _current(node) {}

    reference operator*() { return _current->value; }
    pointer operator->() { return &_current->value; }

    Iterator& operator++() {
        if (_current) _current = _current->next.get();
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const Iterator& other) const { return _current == other._current; }
    bool operator!=(const Iterator& other) const { return _current != other._current; }

private:
    Node* _current;
};
