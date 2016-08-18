#ifndef     _MALL_H_
#define     _MALL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     MAXSIZE     102

typedef struct malloc_node                  //内存池结构体
{
    void                *list;              //内存起点
    struct malloc_node  *next;              //下一个内存池的位置
}node;                                      

typedef struct malloc_head                  //内存池控制
{
    struct malloc_node    *brk;             //整体内存池地址
    int                   size;             //当前内存剩余大小
    void                  *list;            //未分配的内存起点
}head;

int init(head *myhead);
int create(head *myhead, size_t size);
void *insert(head *myhead, size_t size);
void free_mall(head *myhead);
void *mall(head *myhead, int size);

#endif
