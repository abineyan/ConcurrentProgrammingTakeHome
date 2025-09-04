#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include "Linkedlist.h"
#include "Workload.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage %s <n> <m> <mMember> <mInsert> <mDelete>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    double mMember = atof(argv[3]);
    double mInsert = atof(argv[4]);
    double mDelete = atof(argv[5]);

    srand(time(NULL));

    list_init();

    for (int i =0; i < n; i++) {
        int val;
        do {
            val = rand() % 65536;
        } while (Member(val));
        Insert(val);
    }

    workload_t workload = generate_workload(m, mMember, mInsert, mDelete, 0, 65535);
    shuffle_workload(&workload);

    //clock_t start = clock();
    struct timespec t0;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    for (size_t i = 0; i < workload.size; i++) {
        workload_item_t op = workload.items[i];
        switch (op.type) {
            case OP_MEMBER:
                Member(op.value);
                //printf("Member(%d) = %d\n", op.value, Member(op.value));
                break;
            case OP_INSERT:
                Insert(op.value);
                //printf("Insert(%d) done\n", op.value);
                break;
            case OP_DELETE:
                Delete(op.value);
                //printf("Delete(%d) = %d\n", op.value, Delete(op.value));
                break;
        }
//        print_list();
    }
//    clock_gettime(CLOCK_MONOTONIC, &t1);
//    double elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
//    printf("Serial wall-clock time: %.6f s\n", elapsed);

    gettimeofday(&stop, NULL);
    double elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    //printf("Serial wall-clock time: %.0f microseconds\n", elapsed);
    printf("%f\n", elapsed);

//    print_list();
    free_workload(&workload);
    list_free();

    return 0;
}
