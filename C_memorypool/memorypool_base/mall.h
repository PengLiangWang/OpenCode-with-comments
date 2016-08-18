#ifndef     _MALL_H_
#define     _MALL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     MAXSIZE     102

typedef struct malloc_node                  //�ڴ�ؽṹ��
{
    void                *list;              //�ڴ����
    struct malloc_node  *next;              //��һ���ڴ�ص�λ��
}node;                                      

typedef struct malloc_head                  //�ڴ�ؿ���
{
    struct malloc_node    *brk;             //�����ڴ�ص�ַ
    int                   size;             //��ǰ�ڴ�ʣ���С
    void                  *list;            //δ������ڴ����
}head;

int init(head *myhead);
int create(head *myhead, size_t size);
void *insert(head *myhead, size_t size);
void free_mall(head *myhead);
void *mall(head *myhead, int size);

#endif
