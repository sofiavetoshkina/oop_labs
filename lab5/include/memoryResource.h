#pragma once

#include <memory_resource>
#include <vector>
#include <cstddef>

class DynamicMemoryResource : public std::pmr::memory_resource {
public:
    ~DynamicMemoryResource();
    // Для тестов
    size_t allocated_block_count() const {
        return _allocated_blocks.size();
    }
    // Перенесены в public для реализации тестов
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    std::vector<void*> _allocated_blocks;
};
