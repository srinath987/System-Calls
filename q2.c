#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    int inputFile = open(argv[1], O_RDONLY);
    if(inputFile<0){
        perror("error while opening the file!");
        exit(1);
    }
    
    off_t inputFileLength = lseek(inputFile, 0, SEEK_END);
    if (inputFileLength <= 0)
    {
        perror("The input file is empty!");
        exit(1);
    }

    mkdir("Outputs", 0700);
    char outFileAddress[50] = "./Outputs/2_";
    if (strrchr(argv[1], '/') == NULL)
        strcat(outFileAddress, argv[1]);
    else
        strcat(outFileAddress, strrchr(argv[1], '/') + 1);

    int outputFile = open(outFileAddress, O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (outputFile < 0)
    {
        perror("The output file cannot be created!");
        exit(1);
    }
    
    off_t start = atoi(argv[2]);
    off_t end = atoi(argv[3]);
    
    int prefSize = start/500;
    int chunkSize = (prefSize == 0) ? 1 : prefSize;
    int startingChunk = ((start - 1) / chunkSize) * chunkSize;
    int readLength = start - startingChunk;

    char *inp, *out;
    inp = (char *)malloc(chunkSize);
    out = (char *)malloc(chunkSize);

    lseek(inputFile, startingChunk, SEEK_SET);
    double percentage = ((double)readLength / inputFileLength) * 100;

    while (1)
    {
        char percent[10];
        read(inputFile, inp, readLength);
        for (int i = 0, j = readLength - 1; i < readLength; i++, j--)
            out[i] = inp[j];
        write(outputFile, out, readLength);

        
        sprintf(percent, "\r %.2f %%", percentage);
        write(1, percent, 10);
        fflush(stdout);

        if (lseek(inputFile, 0, SEEK_CUR) - chunkSize - readLength < 0)
            break;
        
        lseek(inputFile, -chunkSize - readLength, SEEK_CUR);
        readLength = chunkSize;
        percentage += ((double)readLength / inputFileLength) * 100;
    }

    prefSize = (end - start + 1)/500;
    chunkSize = (prefSize == 0) ? 1 : prefSize;

    free(inp);
    free(out);

    inp = (char *)malloc(chunkSize);
    readLength = chunkSize;
    percentage += ((double)readLength / inputFileLength) * 100;

    lseek(inputFile, start, SEEK_SET);
    while (1)
    {
        char percent[10];
        read(inputFile, inp, readLength);
        write(outputFile, inp, readLength);
        
        sprintf(percent, "\r %.2f %%", percentage);
        write(1, percent, 10);
        fflush(stdout);

        if (lseek(inputFile, 0, SEEK_CUR) > end)
            break;
        if (end - lseek(inputFile, 0, SEEK_CUR) < chunkSize)
            readLength = end - lseek(inputFile, 0, SEEK_CUR)+1;
        else
            readLength = chunkSize;
        percentage += ((double)readLength / inputFileLength) * 100;
    }
    
    prefSize = (inputFileLength - end - 1)/500;
    chunkSize = (prefSize == 0) ? 1 : prefSize;
    startingChunk = ((inputFileLength - end - 2) / chunkSize) * chunkSize;
    readLength = inputFileLength - end - 1 - startingChunk;

    free(inp);
    inp = (char *)malloc(chunkSize);
    out = (char *)malloc(chunkSize);

    lseek(inputFile, end + startingChunk + 1, SEEK_SET);
    percentage += ((double)readLength / inputFileLength) * 100;

    while (1)
    {
        char percent[10];
        read(inputFile, inp, readLength);
        for (int i = 0, j = readLength - 1; i < readLength; i++, j--)
            out[i] = inp[j];
        write(outputFile, out, readLength);
        
        sprintf(percent, "\r %.2f %%", percentage);
        write(1, percent, 10);
        fflush(stdout);

        if (lseek(inputFile, 0, SEEK_CUR) - end - chunkSize - readLength <= 0)
            break;
        
        lseek(inputFile, -chunkSize - readLength, SEEK_CUR);
        readLength = chunkSize;
        percentage += ((double)readLength / inputFileLength) * 100;
    }
        printf("\n");

    close(inputFile);
    close(outputFile);
}
