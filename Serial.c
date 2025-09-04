#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    clock_t start = clock();

    for (size_t i = 0; i < workload.size; i++) {
        workload_item_t op = workload.items[i];
        switch (op.type) {
            case OP_MEMBER:
                printf("Member(%d) = %d\n", op.value, Member(op.value));
                break;
            case OP_INSERT:
                Insert(op.value);
                printf("Insert(%d) done\n", op.value);
                break;
            case OP_DELETE:
                printf("Delete(%d) = %d\n", op.value, Delete(op.value));
                break;
        }
        print_list();
    }


    clock_t end = clock();
    double elapsed = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("Serial execution time for %d operations: %.6f seconds\n", m, elapsed);

    print_list();
    free_workload(&workload);
    list_free();

    return 0;
}
