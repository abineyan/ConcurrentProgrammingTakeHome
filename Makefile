CC = gcc
CFLAGS = -Wall -O2 -pthread

# Common object files
COMMON_OBJS = Linkedlist.o ParallelCommon.o Workload.o

# Targets
all: serial parallel_mutex parallel_rwlock

serial: Serial.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

parallel_mutex: ParallelMutex.o Mutex.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

parallel_rwlock: ParallelRwlock.o Rwlock.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Generic compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o serial parallel_mutex parallel_rwlock