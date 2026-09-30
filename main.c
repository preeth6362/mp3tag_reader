#include<stdio.h>
#include<string.h>
#include "mp3.h"

TAGS tarr[6]={{"TIT2","TITLE"},{"TPE1","ARTIST"},{"TALB","ALBUM"},{"TYER","YEAR"},{"TCON","GENRE"},{"COMM","COMMENt"}};

int main(int argc,char *argv[])
{
    if(argc<=2)
    {
        print_error(argv);
        return 1;
    }
    if(check_operation_type(argv[1])==e_view)
    {
        if(validate_input(argc,argv)!=e_success)
        return 1;
        if(view_contents(tarr)!=e_success)
        {
            printf("Error viewing contents\n");
            return 1;
        }
    }
    else if(check_operation_type(argv[1])==e_edit)
    {
        if(validate_input2(argc,argv)!=e_success)
        return 1;   
    }
    
}
OperationType check_operation_type(char *str)
{
    if(strcmp(str,"-v")==0)
    return e_view;
    if(strcmp(str,"-e")==0)
    return e_edit;
    if(strcmp(str,"--help")==0)
    return e_help;
    else
    {
        printf("unsupported operation type\n");
    return e_unsupported;
    }
}