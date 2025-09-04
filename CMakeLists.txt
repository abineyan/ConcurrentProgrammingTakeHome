cmake_minimum_required(VERSION 4.0)
project(ConcurrentLinkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(ConcurrentLinkedList main.c
        Linkedlist.c
        Linkedlist.h
        Workload.h
        Workload.c
        Serial.c
        Rwlock.c
        ParallelCommon.c
        ParallelCommon.h
        ParallelRwlock.c)

# Link pthread library
find_package(Threads REQUIRED)
target_link_libraries(ConcurrentLinkedList PRIVATE Threads::Threads)