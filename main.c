#include<stdio.h>
#include<string.h>
#include "mp3.h"

TAGS tarr[6]={{"TIT2","TITLE","-t"},{"TPE1","ARTIST","-a"},{"TALB","ALBUM","-A"},{"TYER","YEAR","-y"},{"TCON","GENRE","-g"},{"COMM","COMMENT","-c"}};

int main(int argc,char *argv[])
{
    if(argc==1)
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
    printf("--------------------------------SELECTED EDIT OPERATION-----------------------------\n\n");
        edit_contents(tarr,argv);
    }
    else if(check_operation_type(argv[1])==e_help)
    {
        printf("------------------------------------------------HELP MENU----------------------------\n");
        printf("-v -> to view mp3 file contents\n-e -> to edit mp3 file contents\n2.1. -t -> to edit song title\n2.2. -a -> to edit artist name\n2.3. -A -> to edit album name\n2.4. -y -> to edit year\n2.5. -m -> to edit genre\n2.6. -c -> to edit comment\n\n");
        printf("--------------------------------------------------------------------------------------\n");
    }
    else
    {
        print_error(argv);
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