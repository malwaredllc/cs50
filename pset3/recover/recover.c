#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

// globals
FILE *outptr;
char outname[10];
int filecount = 0;

// prototypes
char *name(void);

int main(int argc, char *argv[])
{
    // display usage information and exit if incorrect number of command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover filename\n");
        return 1;
    }

    // open file to read and check for error
    FILE *inptr = fopen(argv[1], "rb");
    if (!inptr)
    {
        fprintf(stderr, "Error: unable to read file (does not exist or permission denied)\n");
        fclose(inptr);
        return 2;
    }

    // allocate memory for block and check for error
    unsigned char *buf = malloc(BLOCK);
    if (!buf)
    {
        fprintf(stderr, "Error: unable to allocate memory for buffer\n");
        return 3;
    }

    // read data from input file into buffer
    while (fread(buf, BLOCK, sizeof(char), inptr) != 0)
    {
        // if first 4 bytes of block match JPEG file signature then write
        // the content to the output file until the next JPEG signature is found
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && buf[3] >= 0xe0 && buf [3] <= 0xef)
        {
            // if ouptr does not yet point to a file, close it and increment count by 1
            if (outptr)
            {
                fclose(outptr);
            }

            // open output file and check for error
            outptr = fopen(name(), "wb");
            if (!outptr)
            {
                fprintf(stderr, "Error: unable to create new file %s\n", outname);
                fclose(outptr);
                return 2;
            }
        }
        if (outptr)
        {
            fwrite(buf, BLOCK, sizeof(char), outptr);
        }

    }

    // free buffer memory
    free(buf);

    // close file
    fclose(inptr);

    // success
    return 0;
}

char *name(void)
{
    // set filenames incrementally starting at 000.jpg
    if (filecount < 10)
    {
        sprintf(outname, "00%d.jpg", filecount);
    }
    else
    {
        sprintf(outname, "0%d.jpg", filecount);
    }
    filecount++;
    return outname;
}