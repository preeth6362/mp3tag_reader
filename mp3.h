#ifndef MP3_H
#define MP3_H

typedef enum
{
    e_success,
    e_failure
} Status;
typedef enum
{
    e_view,
    e_edit,
    e_help,
    e_unsupported
} OperationType;

typedef struct
{
    char tags[5];
    char tag_name[10];
}TAGS;

void print_error(char *argv[]);
OperationType check_operation_type(char *str);
Status validate_input(int argc,char *argv[]);
Status view_contents(TAGS *tarr);
Status validate_input2(int argc,char *argv[]);
#endif