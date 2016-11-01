#include "mall.h"

/* 初始化大小为 MAXSIZE 的内存池 */
int init(head *myhead)
{
    node *mynode;
    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(MAXSIZE)) == NULL)
    {
        printf("申请内存池失败!\n");
        return -1;
    }

    mynode->next = NULL;
    myhead->size = MAXSIZE;
    myhead->brk = mynode;
    myhead->list = mynode->list;

    printf("初始化成功,当前内存池大小为%d\n", myhead->size);
    printf("init : brk: myhead->brk %ld; list: %d\n", myhead->brk, myhead->brk->list);
    return 0;
}

/* 创建大小为size的新内存池 */
int create(head *myhead, size_t size)
{
    node *mynode;
    node *p = myhead->brk;

    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(size)) == NULL)
    {
        printf("分配内存池失败!\n");
        return -1;
    }

    myhead->size = size;
    mynode->next = NULL;
    
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = mynode;
    myhead->list = mynode->list;

    printf("创建内存池成功,当前内存池大小为%ld\n", size);
    printf("create :mynode->list %ld; myhead->brk %ld; node: %d\n", mynode->list, myhead->brk, mynode);
    return 0;
}

/* 内存池不足时插入大小为size小内存池 */
void *insert(head *myhead, size_t size)
{
    if (myhead == NULL || size <= 0)
    {
        fprintf(stderr, "insert 参数有误(head != NULL or size > 0)\n");
        return NULL;
    }
    node *mynode;
    node *p = myhead->brk;
    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(size)) == NULL)
    {
        printf("分配内存池失败!\n");
        return NULL;
    }

    if (p->next == NULL)
    {
        mynode->next = p;
        myhead->brk = mynode;
    }
    else
    {
        while (p->next->next != NULL)
        {
            p = p->next;
        }
        mynode->next = p->next;
        p->next = mynode;
    }
    printf("插入小内存池成功\n");
    printf("!!!内存池即将不足,请及时创建新内存池\n");
    return mynode->list;
}

/* 释放所有内存池 */
void free_mall(head *myhead)
{
    if (myhead == NULL)
    {
        printf("ERROR: 释放内存地址为空\n");
        return ;
    }
    struct malloc_node *p;

    do
    {
        printf("head->brk : %ld; myhead->brk->next %ld\n", myhead->brk, myhead->brk->next);

        p = myhead->brk;
        myhead->brk = myhead->brk->next;

        free(p->list);
        p->list = NULL;
        p->next = NULL;
        free(p);
        p = NULL;

        printf("free ok\n");
    }while (myhead->brk != NULL);

    return ;   
}

/* 从内存池中分配大小为size的内存供使用 */
void *mall(head *myhead, int size)
{
    if (myhead == NULL || size <= 0)
    {
        fprintf(stderr, "mall 参数有误(head != NULL or size > 0)\n");
        return NULL;
    }
    printf("当前内存池大小为:[%d], 需分配的大小为[%d]\n", myhead->size, size);
    if (size > myhead->size)
    {
        printf("内存不足,插入新内存池\n");
        return insert(myhead, size+1);
    }

    myhead->size -= size;
    myhead->list += size;
    printf("分配内存成功,当前内存池大小为:[%d]\n", myhead->size);
    return myhead->list;
}
