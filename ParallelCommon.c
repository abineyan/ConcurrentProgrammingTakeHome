#define _POSIX_C_SOURCE 200809L
#include "ParallelCommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

static pthread_barrier_t start_barrier;
static pthread_barrier_t end_barrier;

static double timespec_diff_sec(const struct timespec *a, const struct timespec *b) {
    return (double)(b->tv_sec - a->tv_sec) + (double)(b->tv_nsec - a->tv_nsec) * 1e-9;
}

static void* worker_func(void* arg) {
    thread_arg_t* a = (thread_arg_t*)arg;
    sync_ops_t* ops = a->ops;
    pthread_barrier_wait(&start_barrier);

    for (size_t i = 0; i < a->size; ++i) {
        workload_item_t it = a->items[i];
        int result = 0;

        switch (it.type) {
            case OP_MEMBER:
                result = ops->safe_member(it.value);
                //printf("[Thread %d] MEMBER(%d) -> %d\n", a->tid, it.value, result);
                break;
            case OP_INSERT:
                result = ops->safe_insert(it.value);
                //printf("[Thread %d] INSERT(%d) -> %d\n", a->tid, it.value, result);
                break;
            case OP_DELETE:
                result = ops->safe_delete(it.value);
                //printf("[Thread %d] DELETE(%d) -> %d\n", a->tid, it.value, result);
                break;

        (void) result;
        }
    }
    pthread_barrier_wait(&end_barrier);
    return NULL;
}


void run_parallel(int T, workload_t *wl, sync_ops_t* ops) {
    if (T <= 0) { fprintf(stderr,"T must be > 0\n"); return; }
    pthread_t *ths = malloc(sizeof(pthread_t)*T);
    thread_arg_t *args = malloc(sizeof(thread_arg_t)*T);
    size_t base = wl->size / (size_t)T;
    size_t rem = wl->size % (size_t)T;
    size_t start = 0;
    for (int t=0; t<T; ++t) {
        size_t len = base + (t < (int)rem ? 1 : 0);
        args[t].items = wl->items + start;
        args[t].size = len;
        args[t].tid = t;
        args[t].ops = ops;
        args[t].seed = (unsigned int)time(NULL) + t*97;
        start += len;
    }

    pthread_barrier_init(&start_barrier, NULL, (unsigned)(T+1));
    pthread_barrier_init(&end_barrier, NULL, (unsigned)(T+1));

    for (int t=0; t<T; ++t) {
        if (pthread_create(&ths[t], NULL, worker_func, &args[t]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    pthread_barrier_wait(&start_barrier);
    pthread_barrier_wait(&end_barrier);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    for (int t=0; t<T; ++t) pthread_join(ths[t], NULL);

    double elapsed = timespec_diff_sec(&t0, &t1);
    //printf("Parallel run: threads=%d m=%zu time_sec=%.6f\n", T, wl->size, elapsed);
    printf("%f\n", elapsed*1000000);

    pthread_barrier_destroy(&start_barrier);
    pthread_barrier_destroy(&end_barrier);
    free(ths);
    free(args);

}

