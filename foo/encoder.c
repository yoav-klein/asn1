
#include <stdio.h> /* printf */
#include "FooQuestion.h"
#include <string.h> /* memcpy */

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
    FooQuestion_t *foo_question = NULL;
    asn_enc_rval_t status;
    FILE *fp;
    char *filename;

    if(argc < 2)
    {
        usage(argv[0]);
        exit(1);
    }
    foo_question = calloc(1, sizeof(FooQuestion_t)); /* not malloc ! */

    if(!foo_question)
    {
        perror("calloc failed\n");
        exit(1);
    }
    filename = argv[1];

    foo_question->trackingNumber = 2;
    if(-1 == OCTET_STRING_fromBuf(&foo_question->question, "Are you ok?", 10))
    {
        printf("OCTET_STRING_fromBuf failed\n");
        exit(1);
    }

    fp = fopen(filename, "wb");
    if(!fp)
    {
        perror("creating file failed\n");
        exit(1);
    }

    status = der_encode(&asn_DEF_FooQuestion, foo_question, write_out, fp);

    fclose(fp);

    if(status.encoded == -1)
    {
        printf("Couldn't encode rectangle at %s\n", status.failed_type ? 
        status.failed_type->name : "unknown");

        exit(1);
    }

    return 0;
}