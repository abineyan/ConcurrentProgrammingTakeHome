#include <pthread.h>
#include "Linkedlist.h"
#include "ParallelCommon.h"

/* Global RW lock */
static pthread_rwlock_t list_rwlock = PTHREAD_RWLOCK_INITIALIZER;

/* Safe wrappers */
static int rw_member(int value) {
    int res;
    pthread_rwlock_rdlock(&list_rwlock);
    res = Member(value);
    pthread_rwlock_unlock(&list_rwlock);
    return res;
}

static int rw_insert(int value) {
    int res;
    pthread_rwlock_wrlock(&list_rwlock);
    res = Insert(value);
    pthread_rwlock_unlock(&list_rwlock);
    return res;
}

static int rw_delete(int value) {
    int res;
    pthread_rwlock_wrlock(&list_rwlock);
    res = Delete(value);
    pthread_rwlock_unlock(&list_rwlock);
    return res;
}

/* Exported ops table */
sync_ops_t rwlock_ops = {
        .safe_member = rw_member,
        .safe_insert = rw_insert,
        .safe_delete = rw_delete
};
