#include <stdio.h>
#include <stdlib.h>


int main(void)
{
puts("Hello");
    char* buf=malloc(512);
    if (!buf) {
        printf("malloc buf failed\n");
        return -1;
    }

    printf("buf ptr: %p\n", buf);

    snprintf(buf, 1024, "%s", "1234\n");
    printf("buf: %s", buf);

    free(buf);

   
    return 0;
}