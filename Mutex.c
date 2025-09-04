#include <pthread.h>
#include "Linkedlist.h"
#include "ParallelCommon.h"

static pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

static int mutex_member(int value) {
    int res;
    pthread_mutex_lock(&list_mutex);
    res = Member(value);
    pthread_mutex_unlock(&list_mutex);
    return res;
}

static int mutex_insert(int value) {
    int res;
    pthread_mutex_lock(&list_mutex);
    res = Insert(value);
    pthread_mutex_unlock(&list_mutex);
    return res;
}

static int mutex_delete(int value) {
    int res;
    pthread_mutex_lock(&list_mutex);
    res = Delete(value);
    pthread_mutex_unlock(&list_mutex);
    return res;
}

sync_ops_t mutex_ops = {
        .safe_member = mutex_member,
        .safe_insert = mutex_insert,
        .safe_delete = mutex_delete
};
