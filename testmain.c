#include <stdio.h>
#include <stdlib.h>

extern int memcpy2flash(void*dest, void *src, int size);

void *dest_ptr = 0xFFFFFFFF90500003;


int main(int argc, char **argv)
{
    printf ("%s - %s\n", __DATE__, __TIME__);

    unsigned char data[129*1024];
    printf ("0x%016llx - 0x%016llx\n", dest_ptr, dest_ptr + (129*1024));
    memcpy2flash(dest_ptr, data, (129*1024));


    printf ("exit\n");

    return 0;
}

