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
    char* directoryName = argv[3];
    struct stat d;
    int isCreated = stat(directoryName, &d);

    char* string;
    string = (char*)malloc(100*sizeof(char));

    if (isCreated == -1)
    {
        sprintf(string, "Directory is created: No \n");
        write(1, string, strlen(string));
        exit(1);
    }
    else
    {
        sprintf(string, "Directory is created: Yes \n\n");
        write(1, string, strlen(string));
    }

    char* newFileAddress = argv[1];
    char* oldFileAddress = argv[2];

    int newFile = open(argv[1], O_RDONLY);
    if (newFile < 0) {
        perror("Wrong file address!!");
        exit(1);
    }
    off_t newFileLength = lseek(newFile, 0, SEEK_END);
    
    int oldFile = open(argv[2], O_RDONLY);
    if (oldFile < 0) {
        perror("Wrong file address!!");
        exit(1);
    }
    off_t oldFileLength = lseek(oldFile, 0, SEEK_END);
    
    if (newFileLength != oldFileLength) {
        sprintf(string, "Whether file contents are reversed in newfile: No\n\n");
        write(1, string, strlen(string));
    }
    else {
    off_t t = newFileLength;
    int isReverse = 1;
    int prefSize = t/500;
    int chunkSize = (prefSize == 0) ? 1 : prefSize;
    int startingChunk = ((t - 1) / chunkSize) * chunkSize;
    int readLength = t - startingChunk;

    lseek(oldFile, 0, SEEK_SET);
    lseek(newFile, startingChunk, SEEK_SET);
    char *o, *n;
    o = (char*)malloc(chunkSize);
    n = (char*)malloc(chunkSize);

    while (1)
    {
        read(newFile, n, readLength);
        read(oldFile, o, readLength);
        for (int i = 0, j = readLength - 1; i < readLength; i++, j--)
        if (o[i] != n[j]) {
            isReverse = 0;
            break;
        }

        if (lseek(newFile, 0, SEEK_CUR) - chunkSize - readLength < 0)
            break;
        
        lseek(newFile, -chunkSize - readLength, SEEK_CUR);
        readLength = chunkSize;
    }
    
    if (isReverse == 1) {
        sprintf(string, "Whether file contents are reversed in newfile: Yes\n\n");
        write(1, string, strlen(string));
    }
    else {
        sprintf(string, "Whether file contents are reversed in newfile: No\n\n");
        write(1, string, strlen(string));
    }
    
    }

    // permissions for new file
    int newFilePermissions = stat(newFileAddress, &d);
    
    if (d.st_mode & S_IRUSR)
        sprintf(string, "User has read permission on new file: Yes\n");
    else sprintf(string, "User has read permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IWUSR)
        sprintf(string, "User has write permission on new file: Yes\n");
    else sprintf(string, "User has write permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IXUSR)
        sprintf(string, "User has execute permission on new file: Yes\n\n");
    else sprintf(string, "User has execute permission on new file: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IRGRP )
        sprintf(string, "Group has read permission on new file: Yes\n");
    else sprintf(string, "Group has read permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWGRP )
        sprintf(string, "Group has write permission on new file: Yes\n");
    else sprintf(string, "Group has write permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXGRP )
        sprintf(string, "Group has execute permission on new file: Yes\n\n");
    else sprintf(string, "Group has execute permission on new file: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IROTH )
        sprintf(string, "Others has read permission on new file: Yes\n");
    else sprintf(string, "Others has read permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWOTH )
        sprintf(string, "Others has write permission on new file: Yes\n");
    else sprintf(string, "Others has write permission on new file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXOTH )
        sprintf(string, "Others has execute permission on new file: Yes\n\n");
    else sprintf(string, "Others has execute permission on new file: No\n\n");
    
    write(1, string, strlen(string));

    // permissions for old file
    int oldFilePermissions = stat(oldFileAddress, &d);
    
    if (d.st_mode & S_IRUSR)
        sprintf(string, "User has read permission on old file: Yes\n");
    else sprintf(string, "User has read permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IWUSR)
        sprintf(string, "User has write permission on old file: Yes\n");
    else sprintf(string, "User has write permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IXUSR)
        sprintf(string, "User has execute permission on old file: Yes\n\n");
    else sprintf(string, "User has execute permission on old file: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IRGRP )
        sprintf(string, "Group has read permission on old file: Yes\n");
    else sprintf(string, "Group has read permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWGRP )
        sprintf(string, "Group has write permission on old file: Yes\n");
    else sprintf(string, "Group has write permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXGRP )
        sprintf(string, "Group has execute permission on old file: Yes\n\n");
    else sprintf(string, "Group has execute permission on old file: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IROTH )
        sprintf(string, "Others has read permission on old file: Yes\n");
    else sprintf(string, "Others has read permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWOTH )
        sprintf(string, "Others has write permission on old file: Yes\n");
    else sprintf(string, "Others has write permission on old file: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXOTH )
        sprintf(string, "Others has execute permission on old file: Yes\n\n");
    else sprintf(string, "Others has execute permission on old file: No\n\n");
    
    write(1, string, strlen(string));

    // permissions for directory    
    isCreated = stat(directoryName, &d);
    if (d.st_mode & S_IRUSR)
        sprintf(string, "User has read permission on directory: Yes\n");
    else sprintf(string, "User has read permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IWUSR)
        sprintf(string, "User has write permission on directory: Yes\n");
    else sprintf(string, "User has write permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if (d.st_mode & S_IXUSR)
        sprintf(string, "User has execute permission on directory: Yes\n\n");
    else sprintf(string, "User has execute permission on directory: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IRGRP )
        sprintf(string, "Group has read permission on directory: Yes\n");
    else sprintf(string, "Group has read permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWGRP )
        sprintf(string, "Group has write permission on directory: Yes\n");
    else sprintf(string, "Group has write permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXGRP )
        sprintf(string, "Group has execute permission on directory: Yes\n\n");
    else sprintf(string, "Group has execute permission on directory: No\n\n");
    
    write(1, string, strlen(string));

    if(d.st_mode & S_IROTH )
        sprintf(string, "Others has read permission on directory: Yes\n");
    else sprintf(string, "Others has read permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IWOTH )
        sprintf(string, "Others has write permission on directory: Yes\n");
    else sprintf(string, "Others has write permission on directory: No\n");
    
    write(1, string, strlen(string));
    
    if(d.st_mode & S_IXOTH )
        sprintf(string, "Others has execute permission on directory: Yes\n\n");
    else sprintf(string, "Others has execute permission on directory: No\n\n");
    
    write(1, string, strlen(string));

    close(newFile);
    close(oldFile);
}