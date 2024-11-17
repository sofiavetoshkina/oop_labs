#include <iostream>
#include <string>
#include <memory_resource>
#include "memoryResource.h"
#include "queue.h"

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, std::string name) : id(id), name(std::move(name)) {}
};

int main() {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&mem_resource);

    Queue<int, decltype(alloc_int)> int_queue(alloc_int);
    int_queue.push(1);
    int_queue.push(2);
    int_queue.push(3);

    for (auto& item : int_queue) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    Queue<ComplexType, decltype(alloc_complex)> complex_queue(alloc_complex);
    complex_queue.push({1, "Alice"});
    complex_queue.push({2, "Bob"});

    for (auto& item : complex_queue) {
        std::cout << item.id << ": " << item.name << std::endl;
    }

    return 0;
}
