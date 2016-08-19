#include <stdio.h>
#include <stdlib.h>

struct chunk{
    char *freeSp;
    struct chunk *next;
};
struct chunk *chunk_head = NULL;


int main()
{
    struct chunk *c;

    c = (struct chunk *)malloc(1024);
    printf("c:%x\nc->freeSp:%x\n", c, c->freeSp);
    c->freeSp = (char *)c+sizeof(struct chunk);
    c->freeSp[0] = 1;

    printf("sizeof(struct chunk):%x, %d\n", sizeof(struct chunk), sizeof(struct chunk));
    printf("c:%x\nc->freeSp:%x\nc->freeSp[0]:%x\n", c, c->freeSp, c->freeSp[0]);

}
