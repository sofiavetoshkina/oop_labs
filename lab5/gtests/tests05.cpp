#include <gtest/gtest.h>
#include <string>
#include <memory_resource>

#include "memoryResource.h"
#include "queue.h"

// Проверка работы с простыми типами
TEST(QueueTest, PushPopInt) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);

    Queue<int, decltype(alloc_int)> queue(alloc_int);
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);

    EXPECT_EQ(queue.pop(), 1);
    EXPECT_EQ(queue.pop(), 2);
    EXPECT_EQ(queue.size(), 1);

    EXPECT_EQ(queue.pop(), 3);

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

// Проверка работы с сложными типами
struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, std::string name) : id(id), name(std::move(name)) {}

    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name;
    }
};

TEST(QueueTest, PushPopComplexType) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&mem_resource);

    Queue<ComplexType, decltype(alloc_complex)> queue(alloc_complex);
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);

    queue.push(ComplexType{1, "Соня"});
    queue.push(ComplexType{2, "Никита"});
    queue.push(ComplexType{3, "Елена"});

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);

    EXPECT_EQ(queue.pop(), (ComplexType{1, "Соня"}));
    EXPECT_EQ(queue.pop(), (ComplexType{2, "Никита"}));
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.pop(), (ComplexType{3, "Елена"}));

    EXPECT_TRUE(queue.empty());
}

// Проверка работы итератора
TEST(QueueTest, IteratorTest) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);

    Queue<int, decltype(alloc_int)> queue(alloc_int);
    queue.push(10);
    queue.push(20);
    queue.push(30);

    auto it = queue.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, queue.end());
}

// Проверка работы с пустой очередью
TEST(QueueTest, EmptyQueuePopThrows) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);

    Queue<int, decltype(alloc_int)> queue(alloc_int);
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

// Проверка наполнения/извлечения из очереди
TEST(QueueTest, SequentialPushPop) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&mem_resource);

    Queue<int, decltype(alloc_int)> queue(alloc_int);
    for (int i = 0; i < 100; ++i) {
        queue.push(i);
    }
    EXPECT_EQ(queue.size(), 100);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(queue.pop(), i);
    }
    EXPECT_TRUE(queue.empty());
}

// Проверка работы с перемещением
TEST(QueueTest, MoveSemantics) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<std::string> alloc_str(&mem_resource);

    Queue<std::string, decltype(alloc_str)> queue(alloc_str);
    std::string s = "ТЕСТ";
    queue.push(std::move(s));

    EXPECT_TRUE(s.empty()); // После перемещения строка должна быть пуста
    EXPECT_EQ(queue.pop(), "ТЕСТ");
}

// Проверка итератора на сложные типы
TEST(QueueTest, IteratorComplexType) {
    DynamicMemoryResource mem_resource;
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&mem_resource);

    Queue<ComplexType, decltype(alloc_complex)> queue(alloc_complex);
    queue.push({1, "Никита"});
    queue.push({2, "Соня"});
    queue.push({3, "Елена"});

    auto it = queue.begin();
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->name, "Никита");
    ++it;
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->name, "Соня");
    ++it;
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->name, "Елена");
}

// Проверка выделения и освобождения памяти
TEST(MemoryResourceTest, AllocationDeallocation) {
    DynamicMemoryResource mem_resource;

    // Изначально нет выделенных блоков
    EXPECT_EQ(mem_resource.allocated_block_count(), 0);

    // Выделение памяти через аллокатор
    void* ptr1 = mem_resource.do_allocate(64, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 1);

    void* ptr2 = mem_resource.do_allocate(128, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 2);

    void* ptr3 = mem_resource.do_allocate(256, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 3);

    // Освобождение памяти
    mem_resource.do_deallocate(ptr1, 64, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 2);

    mem_resource.do_deallocate(ptr2, 128, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 1);

    mem_resource.do_deallocate(ptr3, 256, 8);
    EXPECT_EQ(mem_resource.allocated_block_count(), 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}