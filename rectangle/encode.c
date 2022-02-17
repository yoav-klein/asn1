
#include <stdio.h> /* printf */
#include "Rectangle.h"
#include <string.h> /* memcpy */

/* write the encoded content into a FILE stream */


int write_out(const void *buffer, size_t size, void *app_key)
{
    char *runner = NULL;
    int i = 0;
    FILE *output = (FILE*)app_key;
    
    size_t written_bytes = fwrite(buffer, 1, size, output);

    return (written_bytes == size ? 0 : -1);
}

void usage(char *prog)
{
    printf("Usage: %s filename\n", prog);
}

int main(int argc, char **argv)
{
    Rectangle_t *rectangle = NULL;
    asn_enc_rval_t status;
    FILE *fp;
    char *filename;

    if(argc < 2)
    {
        usage(argv[0]);
        exit(1);
    }
    rectangle = calloc(1, sizeof(Rectangle_t)); /* not malloc ! */

    if(!rectangle)
    {
        perror("calloc failed\n");
        exit(1);
    }
    filename = argv[1];

    rectangle->height = 100;
    rectangle->width = 60;

    fp = fopen(filename, "wb");
    if(!fp)
    {
        perror("creating file failed\n");
        exit(1);
    }

    status = der_encode(&asn_DEF_Rectangle, rectangle, write_out, fp);

    fclose(fp);

    if(status.encoded == -1)
    {
        printf("Couldn't encode rectangle at %s\n", status.failed_type ? 
        status.failed_type->name : "unknown");

        exit(1);
    }
}