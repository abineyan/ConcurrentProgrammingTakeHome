#ifndef CONCURRENTLINKEDLIST_PARALLELCOMMON_H
#define CONCURRENTLINKEDLIST_PARALLELCOMMON_H

#include "Workload.h"
#include <stddef.h>
#include <pthread.h>

typedef int (*safe_op_fn)(int value);

typedef struct {
    safe_op_fn safe_member;
    safe_op_fn safe_insert;
    safe_op_fn safe_delete;
} sync_ops_t;

typedef struct {
    workload_item_t* items;
    size_t size;
    int tid;
    sync_ops_t* ops;
    unsigned int seed;
} thread_arg_t;

void run_parallel(int T, workload_t *wl, sync_ops_t* ops);

#endif //CONCURRENTLINKEDLIST_PARALLELCOMMON_H
