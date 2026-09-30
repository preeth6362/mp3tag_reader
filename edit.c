#include<stdio.h>
#include<string.h>
#include "mp3.h"

FILE *fptr_e;
Status validate_input2(int argc,char *argv[])
{
    if(argc>5 || argc<5)
    {
        print_error(argv);
        return e_failure;
    }
    if((strcmp(argv[2],"-t")!=0) || (strcmp(argv[2],"-a")!=0) || (strcmp(argv[2],"-A")!=0) || (strcmp(argv[2],"-y")!=0) || (strcmp(argv[2],"-g")!=0) || (strcmp(argv[2],"-c")!=0))
    {
        print_error(argv);
        return e_failure;
    }
    fptr_e=fopen(argv[4],"rb");
    if(fptr_e==NULL)
    {
        printf("Error opening file\n");
        return e_failure;
    }
    char buff[4];
    fread(buff,3,1,fptr_e);
    buff[3]='\0';
    if(strcmp(buff,"ID3")!=0)
    {
        printf("this is not a mp3 file\n");
        return e_failure;
    }
    return e_success;
}