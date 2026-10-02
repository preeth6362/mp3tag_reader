#include<stdio.h>
#include<string.h>
#include "mp3.h"

FILE *fptr_v;

void print_error(char *argv[])
{
    printf("Error :");
        for(int i=0;argv[i]!=NULL;i++)
        printf("%s ",argv[i]);
        printf(": INVALID ARGUMENTS\nUSAGE :\n");
        printf("To view the content of file please enter: ./a.out -v mp3filename\n");
        printf("To edit the content of file please enter: ./a.out -e -t/-a/-A/-g/-y/-c changing_text mp3filename\n");
        printf("To get help please enter: ./a.out --help\n");
}
Status validate_input(int argc,char *argv[])
{
    if(argc!=3)
    {
        print_error(argv);
        return e_failure;
    }
    fptr_v=fopen(argv[2],"rb");
    if(fptr_v==NULL)
    {
        printf("Error opening file\n");
        return e_failure;
    }
    char buff[4];
    fread(buff,3,1,fptr_v);
    buff[3]='\0';
    if(strcmp(buff,"ID3")!=0)
    {
        printf("this is not a mp3 file\n");
        return e_failure;
    }
    return e_success;
}
Status view_contents(TAGS *tarr)
{
    fseek(fptr_v,10,SEEK_SET);
    printf("--------------------------------------Displaying contents of File-----------------------------------\n\n");
    printf("------------------------Name-------------------------Content----------------------------------------\n");
    int i=0;
    while(i<6)
    {
    char buff[5];
    fread(buff,4,1,fptr_v);
    buff[4]='\0';
    unsigned int size;
    fread(&size,4,1,fptr_v);
    size=(size>>24)|(size>>8 & (0x0000FF00))|(size<<8 &(0x00FF0000))|(size<<24);
    fseek(fptr_v,3,SEEK_CUR);
    char buff1[size];
    fread(buff1,size-1,1,fptr_v);
    buff1[size-1]='\0';
    int j;
    for(j=0;j<6;j++)
    {
        if(strcmp(buff,tarr[j].tags)==0)
        {
             printf("\t\t\t%s\t\t\t%s\n",tarr[j].tag_name,buff1);
             i++;
        break;
        }
    }
    }
    printf("\n-------------------contents displayed successfully--------------------------------\n");
    fclose(fptr_v);
    return e_success;
}