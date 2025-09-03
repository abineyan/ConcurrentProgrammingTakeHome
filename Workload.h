// workload.h
#ifndef WORKLOAD_H
#define WORKLOAD_H

#include <stddef.h>

typedef enum {
    OP_MEMBER,
    OP_INSERT,
    OP_DELETE
} operation_t;

typedef struct {
    operation_t type;
    int value;
} workload_item_t;

typedef struct {
    workload_item_t* items;
    size_t size;
} workload_t;

workload_t generate_workload(size_t m, double mMember, double mInsert, double mDelete, int min_val, int max_val);

void shuffle_workload(workload_t* workload);

workload_t get_thread_workload(workload_t* workload, size_t thread_id, size_t num_threads);

void free_workload(workload_t* workload);


#endif // WORKLOAD_H