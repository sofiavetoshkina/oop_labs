#include <algorithm>
#include <new>

#include "memoryResource.h"

void* DynamicMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    _allocated_blocks.push_back(ptr);
    return ptr;
}

void DynamicMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    auto it = std::find(_allocated_blocks.begin(), _allocated_blocks.end(), p);
    if (it != _allocated_blocks.end()) {
        _allocated_blocks.erase(it);
        ::operator delete(p, std::align_val_t(alignment));
    }
}

bool DynamicMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

DynamicMemoryResource::~DynamicMemoryResource() {
    for (void* block : _allocated_blocks) {
        ::operator delete(block);
    }
    _allocated_blocks.clear();
}
