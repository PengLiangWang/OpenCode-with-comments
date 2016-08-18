#include "mall.h"

/* ��ʼ����СΪ MAXSIZE ���ڴ�� */
int init(head *myhead)
{
    node *mynode;
    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(MAXSIZE)) == NULL)
    {
        printf("�����ڴ��ʧ��!\n");
        return -1;
    }

    mynode->next = NULL;
    myhead->size = MAXSIZE;
    myhead->brk = mynode;
    myhead->list = mynode->list;

    printf("��ʼ���ɹ�,��ǰ�ڴ�ش�СΪ%d\n", myhead->size);
    printf("init : brk: myhead->brk %ld; list: %d\n", myhead->brk, myhead->brk->list);
    return 0;
}

/* ������СΪsize�����ڴ�� */
int create(head *myhead, size_t size)
{
    node *mynode;
    node *p = myhead->brk;

    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(size)) == NULL)
    {
        printf("�����ڴ��ʧ��!\n");
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

    printf("�����ڴ�سɹ�,��ǰ�ڴ�ش�СΪ%ld\n", size);
    printf("create :mynode->list %ld; myhead->brk %ld; node: %d\n", mynode->list, myhead->brk, mynode);
    return 0;
}

/* �ڴ�ز���ʱ�����СΪsizeС�ڴ�� */
void *insert(head *myhead, size_t size)
{
    if (myhead == NULL || size <= 0)
    {
        fprintf(stderr, "insert ��������(head != NULL or size > 0)\n");
        return NULL;
    }
    node *mynode;
    node *p = myhead->brk;
    mynode = (node *)malloc(sizeof(node));
    if ((mynode->list = malloc(size)) == NULL)
    {
        printf("�����ڴ��ʧ��!\n");
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
    printf("����С�ڴ�سɹ�\n");
    printf("!!!�ڴ�ؼ�������,�뼰ʱ�������ڴ��\n");
    return mynode->list;
}

/* �ͷ������ڴ�� */
void free_mall(head *myhead)
{
    if (myhead == NULL)
    {
        printf("ERROR: �ͷ��ڴ��ַΪ��\n");
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

/* ���ڴ���з����СΪsize���ڴ湩ʹ�� */
void *mall(head *myhead, int size)
{
    if (myhead == NULL || size <= 0)
    {
        fprintf(stderr, "mall ��������(head != NULL or size > 0)\n");
        return NULL;
    }
    printf("��ǰ�ڴ�ش�СΪ:[%d], �����Ĵ�СΪ[%d]\n", myhead->size, size);
    if (size > myhead->size)
    {
        printf("�ڴ治��,�������ڴ��\n");
        return insert(myhead, size+1);
    }

    myhead->size -= size;
    myhead->list += size;
    printf("�����ڴ�ɹ�,��ǰ�ڴ�ش�СΪ:[%d]\n", myhead->size);
    return myhead->list;
}
