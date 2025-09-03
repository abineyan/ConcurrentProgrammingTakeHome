#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Workload.h"

static int rand_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

workload_t generate_workload(size_t m, double mMember, double mInsert, double mDelete, int min_val, int max_val) {
    workload_t wl;
    wl.size = m;
    wl.items = malloc(sizeof(workload_item_t) * m);
    if (!wl.items){
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    size_t numMember = (size_t)(m * mMember);
    size_t numInsert = (size_t)(m * mInsert);
    size_t numDelete = (size_t)(m * mDelete);

    size_t idx = 0;
    for (size_t i = 0; i < numMember; ++i, ++idx) {
        wl.items[idx].type = OP_MEMBER;
        wl.items[idx].value = rand_range(min_val, max_val);
    }
    for (size_t i = 0; i < numInsert; ++i, ++idx) {
        wl.items[idx].type = OP_INSERT;
        wl.items[idx].value = rand_range(min_val, max_val);
    }
    for (size_t i = 0; i < numDelete; ++i, ++idx) {
        wl.items[idx].type = OP_DELETE;
        wl.items[idx].value = rand_range(min_val, max_val);
    }

    shuffle_workload(&wl);
    return wl;
}

void shuffle_workload(workload_t* wl) {
    if (!wl || !wl->items) return;
    for (size_t i = wl->size - 1; i > 0; --i) {
        size_t j = rand_range(0, i);
        workload_item_t tmp = wl->items[i];
        wl->items[i] = wl->items[j];
        wl->items[j] = tmp;
    }
}

workload_t get_thread_workload(workload_t *wl, size_t thread_id, size_t num_threads) {
    workload_t twl;
    if (!wl || !wl->items || num_threads == 0) {
        twl.items = NULL;
        twl.size = 0;
        return twl;
    }

    size_t base = wl->size / num_threads;
    size_t remainder = wl->size % num_threads;
    size_t start = thread_id * base + (thread_id < remainder ? thread_id : remainder);
    size_t end = start + base + (thread_id < remainder ? 1 : 0);

    twl.size = end - start;
    twl.items = wl->items + start;
    return twl;
}

void free_workload(workload_t* wl) {
    if (wl && wl->items) {
        free(wl->items);
        wl->items = NULL;
        wl->size = 0;
    }
}