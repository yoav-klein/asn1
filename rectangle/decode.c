
#include <unistd.h> /* close */
#include "Rectangle.h"


void print_bytes(char *buff, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        printf("0x%x ", buff[i]);
    }
    printf("\n");
}

void usage(char *prog)
{
    printf("Usage: %s filename\n", prog);
}

int main(int argc, char **argv)
{
    size_t i = 0;
    char buff[1024]; /* temporary buffer */
    asn_dec_rval_t status;
    Rectangle_t *rectangle;
    FILE *fp;
    size_t bytes_read = 0;
    char *filename;

    if(argc < 2)
    {
        usage(argv[0]);
        exit(1);
    }
    filename = argv[1];
    
    fp = fopen(filename, "rb");
    if(!fp)
    {
        perror(filename);
        exit(1);
    }

    bytes_read = fread(buff, 1, sizeof(buff), fp);
    fclose(fp);
    if(!bytes_read)
    {
        printf("couldn't read from file\n");
        exit(1);
    }

    /*print_bytes(buff, bytes_read);*/ /* good for diagnostics */

    status = ber_decode(0, &asn_DEF_Rectangle, (void**)&rectangle, buff, bytes_read);
    if(status.code != RC_OK)
    {
        fprintf(stderr, "Broken Rectangle encoding at byte: %ld\n", status.consumed);
        exit(1);
    }

    xer_fprint(stdout, &asn_DEF_Rectangle, rectangle);

    return 0;

}