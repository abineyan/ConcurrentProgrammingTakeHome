gcc -Wall -O2 -pthread ParallelRwlock.c Rwlock.c ParallelCommon.c Linkedlist.c Workload.c -o parallel_rwlock
gcc -o serial Serial.c Linkedlist.c Workload.c -std=c11 -Wall -Wextra
gcc -Wall -O2 -pthread ParallelMutex.c Mutex.c ParallelCommon.c Linkedlist.c Workload.c -o parallel_mutex