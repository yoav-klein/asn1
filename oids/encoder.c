
#include <stdio.h> /* printf */
#include "Mechanism.h"
#include <stdlib.h> /* malloc */

/* write the encoded content into a FILE stream */


int write_out(const void *buffer, size_t size, void *app_key)
{
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
    Mechanism_t *mechanism = NULL;
    asn_enc_rval_t status;
    FILE *fp;
    char *filename;
    uint8_t *demo_oid = malloc(4 * sizeof(uint8_t));

    demo_oid[0] = 1;
    demo_oid[1] = 2;
    demo_oid[2] = 3;
    demo_oid[3] = 4;

    if(argc < 2)
    {
        usage(argv[0]);
        exit(1);
    }
    mechanism = calloc(1, sizeof(Mechanism_t)); /* not malloc ! */

    mechanism->oid.size = 4;
    mechanism->oid.buf = demo_oid;

    if(!mechanism)
    {
        perror("calloc failed\n");
        exit(1);
    }
    filename = argv[1];

    
    fp = fopen(filename, "wb");
    if(!fp)
    {
        perror("creating file failed\n");
        exit(1);
    }

    status = der_encode(&asn_DEF_Mechanism, mechanism, write_out, fp);

    fclose(fp);

    if(status.encoded == -1)
    {
        printf("Couldn't encode rectangle at %s\n", status.failed_type ? 
        status.failed_type->name : "unknown");

        exit(1);
    }

    free(demo_oid);
    return 0;
}