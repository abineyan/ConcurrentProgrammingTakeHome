// ParallelRwlock.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Linkedlist.h"
#include "Workload.h"
#include "ParallelCommon.h"

// bring in ops table from Rwlock.c
extern sync_ops_t rwlock_ops;

int main(int argc, char* argv[]) {
    if (argc != 7) {
        fprintf(stderr,
                "Usage: %s <threads> <n> <m> <mMember> <mInsert> <mDelete>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    int T       = atoi(argv[1]);
    int n       = atoi(argv[2]);
    size_t m    = (size_t) atol(argv[3]);
    double fM   = atof(argv[4]);
    double fI   = atof(argv[5]);
    double fD   = atof(argv[6]);

    if (T <= 0) {
        fprintf(stderr, "threads must be > 0\n");
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));

    list_init();
    int inserted = 0;
    while (inserted < n) {
        int val = rand() % 65536;
        if (Insert(val)) inserted++;  // Insert ensures sorted + unique
    }

    workload_t wl = generate_workload(m, fM, fI, fD, 0, 65535);
    shuffle_workload(&wl);

    run_parallel(T, &wl, &rwlock_ops);

    if (n <= 20 && wl.size <= 50) {
        print_list();
    } else {
        printf("Final list size: %zu\n", list_count());
    }

    /* 4) cleanup */
    free_workload(&wl);
    list_free();

    return EXIT_SUCCESS;
}
