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
    if(!((strcmp(argv[2],"-t")==0) || (strcmp(argv[2],"-a")==0) || (strcmp(argv[2],"-A")==0) || (strcmp(argv[2],"-y")==0) || (strcmp(argv[2],"-g")==0) || (strcmp(argv[2],"-c")==0)))
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
Status edit_contents(TAGS *tarr,char *argv[])
{
    rewind(fptr_e);
    FILE *temp=fopen("tempo.mp3","wb");
    char buff[10];
    fread(buff,10,1,fptr_e);
    fwrite(buff,10,1,temp);
    char buff1[5];
    int i;
    do
    {
    fread(buff1,4,1,fptr_e);
    buff1[4]='\0';
    fwrite(buff1,4,1,temp);
    for(i=0;i<6;i++)
    {
        if(strcmp(tarr[i].inp,argv[2])==0 && strcmp(tarr[i].tags,buff1)==0)
        break;
    }
    unsigned int osize;
    fread(&osize,4,1,fptr_e);
    unsigned int osize1=(osize>>24)|(osize>>8 & (0x0000FF00))|(osize<<8 &(0x00FF0000))|(osize<<24);
    if(i<6)
    {
        unsigned int size=strlen(argv[3])+1;
        unsigned int size1=(size>>24)|(size>>8 & (0x0000FF00))|(size<<8 &(0x00FF0000))|(size<<24);
        fwrite(&size1,4,1,temp);
        char buff2[3];
        fread(buff2,3,1,fptr_e);
        fwrite(buff2,3,1,temp);
        fwrite(argv[3],size-1,1,temp);
        fseek(fptr_e,osize1-1,SEEK_CUR);
    }
    else
    {
    fwrite(&osize,4,1,temp);
    char buff2[3];
    fread(buff2,3,1,fptr_e);
    fwrite(buff2,3,1,temp);
    char buff3[osize1-1];
    fread(buff3,osize1-1,1,fptr_e);
    fwrite(buff3,osize1-1,1,temp);
    }
   }while(i==6);
   int ch;
   while((ch=getc(fptr_e))!=EOF)
   {
    putc(ch,temp);
   }
   fclose(fptr_e);
   fclose(temp);
   return e_success;
}