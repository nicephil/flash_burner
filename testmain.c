#include <stdio.h>
#include <stdlib.h>

extern int memcpy2flash(void*dest, void *src, int size);

unsigned char data[10020*1024] = {0xFF};

int main(int argc, char **argv)
{
    printf ("0x%08x - 0x%08x\n", 0x80500008, 0x80500008+(10020*1024)); 
    memcpy2flash((void*)0x80500008, data, (10020*1024));

    return 0;
}

