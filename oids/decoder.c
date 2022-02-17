
#include <unistd.h> /* close */
#include "Mechanism.h"

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
    char buff[1024]; /* temporary buffer */
    asn_dec_rval_t status;
    Mechanism_t *mechanism = NULL;

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

    print_bytes(buff, bytes_read); /* good for diagnostics */

    status = ber_decode(0, &asn_DEF_Mechanism, (void**)&mechanism, buff, bytes_read);
    if(status.code != RC_OK)
    {
        fprintf(stderr, "Broken FooQuestion encoding at byte: %ld\n", status.consumed);
        exit(1);
    }
    
    xer_fprint(stdout, &asn_DEF_Mechanism, mechanism);

    return 0;

}