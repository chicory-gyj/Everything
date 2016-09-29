#include <stdio.h>
#include <stdlib.h>

unsigned char Key[]=
{
    0xf, 0xe, 0xe, 0xa,
    0xc, 0x8, 0x7, 0x9,
    0xc, 0x6, 0x1, 0x0,
    0x0, 0x7, 0x2, 0x4
};

void AES_ENCRYPT(unsigned char *buffer, int *buffer_len)
{
    int i = 0;

    int blocknum = (*buffer_len % 16) ? ((*buffer_len / 16) + 1): \
        (*buffer_len / 16);

    printf("blocknum: (%d) buffer_len: (%d)", blocknum, *buffer_len);
    char *ptr = buffer;
    for(i = 0; i < blocknum; i++)
    {
        AES128_ECB_encrypt(ptr, Key, ptr);
        ptr += 16;
    }
    printf("AES ENCRYPT OK:");
    *buffer_len = blocknum * 16;
    //printHexBuffer(buffer, blocknum * 16);
}

int AES_DECRYPT(unsigned char *buffer, int *buffer_len)
{
    int i = 0;

    int blocknum = (*buffer_len % 16) ? ((*buffer_len / 16) + 1): \
        (*buffer_len / 16);

    printf("\nblocknum: (%d) buffer_len: (%d)", blocknum, *buffer_len);
    char *ptr = buffer;
    for(i = 0; i < blocknum; i++)
    {
        AES128_ECB_decrypt(ptr, Key, ptr);
        ptr += 16;
    }
    printf("\nAES DECRYPT OK:");
    *buffer_len = strlen(buffer);
    printf("\nDecrypt: %s", buffer);
    //printHexBuffer(buffer, blocknum * 16);
}

int main()
{
    char *source = NULL;
    int source_size;
    FILE *fp = fopen("111.bcp", "r");
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            source_size = bufsize;
            printf("bufsize: %d\n", bufsize);
            if (bufsize == -1) { /* Error */ }

            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }
    //printf("\nbuffer: %s\n", source);
    //AES_ENCRYPT(source, &source_size);
    AES_DECRYPT(source, &source_size);

    free(source); /* Don't forget to call free() later! */

}
