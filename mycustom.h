#ifndef _MYCUSTOM_H_
#define _MYCUSTOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@number_error: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@modified_env: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int number_error;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int modified_env;
    int status;

    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;

} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

int file_exe_cmd(info_t *, char *);
char *replicate_characters(char *, int, int);
char *finding_string_path(info_t *, char *, char *);

int hsh(info_t *, char **);
int _builtin_cmd_search(info_t *);
void _cmd_search(info_t *);
void _cmd_split(info_t *);

int loophsh(char **);

int my_strlen(char *);
int my_strcmp(char *, char *);
char *begin_here(const char *, const char *);
char *my_strcat(char *, char *);

void _myputs(char *);
int _myputchar(char);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);

char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

char **split_into_words(char *, char *);
char **split_into_words2(char *, char);

char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

int release_ptr(void **);

char *my_mem_set(char *, char, unsigned int);
void release_str(char **);
void *mem_realloc(void *, unsigned int, unsigned int);

int atoi_errs(char *);
void printerr(info_t *, char *);
int output_decimal(int, int);
char *digit_converter(long int, int, int);
void delete_remarks(char *);

int interactive(info_t *);
int my_delimiter(char, char *);
int _alphabet(int);
int string_converter(char *);

int my_exit(info_t *);
int _cd(info_t *);
int _help(info_t *);

ssize_t input_minus_newline(info_t *);
int buf_getline(info_t *, char **, size_t *);
void sigintHandler(int);

int display_history_list(info_t *);
int _alias(info_t *);

char *my_getenv(info_t *, const char *);
int _env(info_t *);
int set_myenv(info_t *);
int unset_myenv(info_t *);
int fill_up_linked_env(info_t *);

void initiating_info(info_t *);
void setting_up_info(info_t *, char **);
void clearing_info(info_t *, int);

char *file_history_path(info_t *info);
int create_file_history(info_t *info);
int history_recall(info_t *info);
int create_list_of_history(info_t *info, char *buf, int linecount);
int history_recounts(info_t *info);

char **getenv_copy(info_t *);
int my_unsetenv(info_t *, char *);
int my_setenv(info_t *, char *, char *);

int chain_is_true(info_t *, char *, size_t *);
void checking_the_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_changed(info_t *);
int vars_changed(info_t *);
int string_changed(char **, char *);

size_t length_linked_list(const list_t *);
char **strs_list(list_t *);
size_t list_output(const list_t *);
list_t *node_begins_here(list_t *, char *, char);
ssize_t fetch_first_node(list_t *, list_t *);

list_t *node_tolist_index(list_t **, const char *, int);
list_t *append_end_node(list_t **, const char *, int);
size_t print_strings_list(const list_t *);
int remove_first_node(list_t **, unsigned int);
void give_up_list(list_t **);

#endif
