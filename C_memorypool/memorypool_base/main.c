#include "mall.h"

int main()
{
    head    myhead;
    char    *p;

    if (init(&myhead) == -1)
    {
        printf("��ʼ��ʧ��\n");
        return -1;
    }
    else
        printf("��ʼ���ɹ�\n");

    if ((p = (char *)mall(&myhead, 10)) == NULL)
    {
        printf("mall �ڴ�ʧ��\n");
        return -1;
    }
    create(&myhead, 100);
    if ((p = (char *)mall(&myhead, 111)) == NULL)
    {
        printf("mall �ڴ�ʧ��\n");
        return -1;
    }
    if ((p = (char *)mall(&myhead, 10)) == NULL)
    {
        printf("mall �ڴ�ʧ��\n");
        return -1;
    }
    memcpy(p, "Chinaese", 8);
    printf("p : %s\n", p);

    create(&myhead, 100);

    free_mall(&myhead);

    return 0;
}
