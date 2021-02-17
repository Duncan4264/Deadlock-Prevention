#define _GNU_SOURCE
#include <pthread.h>

#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *call(void *caller) {
    int i;
    char *s = caller;
    for (i = 0; i < 4; ++i) {
        pthread_mutex_lock(&mutex);
        printf("%s %d\n", s, i);
        sleep(1);
        pthread_mutex_unlock(&mutex);
#if 0
        pthread_yield();
#endif
    }
    return NULL;
}

int main() {
    int i;
    for (i = 0; i < 4; ++i) {
        pthread_t t1, t2, t3, t4;
        printf("================================\n");
        pthread_create(&t1, NULL, call, "Russia");
        pthread_create(&t2, NULL, call, "     Scotland");
        pthread_create(&t3, NULL, call, "            Germany");
        pthread_create(&t4, NULL, call, "                 Norway");
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
        pthread_join(t4, NULL);
    }
    return 0;
}
