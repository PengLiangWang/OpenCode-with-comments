#define THREAD 32
#define QUEUE  256

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "threadpool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;

typedef struct tb_fans{
    char localdate[9];
    char locallogNo[7];
    char localTime[7];
    int  a;
}tBfans;

void dummy_task(void *arg) {
    usleep(100);
    pthread_mutex_lock(&lock);
    /* 记录成功完成的任务数 */
    /*
    tBfans *tfans;
    tfans = (tBfans *)arg;
    */
    int a;
    a = *(int *)arg;
    //printf("localdate: %s\ta: %d\n", tfans->localdate, tfans->a);
    printf("a: %d\n", a);
    done++;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    threadpool_t *pool;
    tBfans  tbfans;
    memset(&tbfans, 0x00, sizeof(tBfans));
    strncpy(tbfans.localdate, "20161027" ,8);
    strncpy(tbfans.locallogNo, "347589", 6);
    strncpy(tbfans.localTime, "110223", 6);

    /* 初始化互斥锁 */
    pthread_mutex_init(&lock, NULL);

    /* 断言线程池创建成功,  pool即为创建返回的线程池*/
    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    fprintf(stderr, "Pool started with %d threads and "
            "queue size of %d\n", THREAD, QUEUE);

    /* 只要任务队列还没满，就循环一直添加 */
    /*
    while(threadpool_add(pool, &dummy_task, (void *)&tbfans, 0) == 0) {
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
    }
    */
    /*只添加一个任务*/
    int i;
    for(i=0; i<5; i++)
    {    
        tbfans.a = i;
        printf("tbfans.a: %d\n", tbfans.a);
        if(threadpool_add(pool, &dummy_task, (void *)&tbfans.a, 0) == 0) {
            pthread_mutex_lock(&lock);
            tasks++;
            pthread_mutex_unlock(&lock);
        }
    }

    fprintf(stderr, "Added %d tasks\n", tasks); 

    /* 不断检查任务数是否完成一半以上，没有则继续休眠 */
    /*
    while((tasks / 2) > done) {
        usleep(10000);
    }
    */
    /* 这时候销毁线程池,0 代表 immediate_shutdown , 1代表执行完线程池中所有线程才销毁*/
    assert(threadpool_destroy(pool, 1) == 0);
    fprintf(stderr, "Did %d tasks\n", done);   /*完成了多少任务*/

    return 0;
}
