#include "mall.h"

int main()
{
    head    myhead;
    char    *p;

    if (init(&myhead) == -1)
    {
        printf("初始化失败\n");
        return -1;
    }
    else
        printf("初始化成功\n");

    if ((p = (char *)mall(&myhead, 10)) == NULL)
    {
        printf("mall 内存失败\n");
        return -1;
    }
    create(&myhead, 100);
    if ((p = (char *)mall(&myhead, 111)) == NULL)
    {
        printf("mall 内存失败\n");
        return -1;
    }
    if ((p = (char *)mall(&myhead, 10)) == NULL)
    {
        printf("mall 内存失败\n");
        return -1;
    }
    memcpy(p, "Chinaesesssss", 12);
    printf("p : %s\n", p);

    create(&myhead, 100);

    free_mall(&myhead);

    return 0;
}
