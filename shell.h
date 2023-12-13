#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

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
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line num count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
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


/* loophsh.c */
int loophsh(char **);

/* error.c */
void _pinputstr(char *);
int _writchar(char);
int _writchar_fd(char c, int fd);
int _pinputstr_fd(char *str, int fd);

/* exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* atshell.c */
int interactive(info_t *);
int is_delim(char, char *);
int is_alpha_char(int);
int _atoi(char *);

/* error_handlers.c */
int _convstr_int(char *);
void print_error(info_t *, char *);
int print_deci(int, int);
char *convert_number(long int, int, int);
void replace_comments(char *);

/* built_in.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* built_in_handlers.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* environment.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* get_environment.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* getinfo.c */
void initialize_struct(info_t *);
void set_struct_info(info_t *, char **);
void free_info_struct(info_t *, int);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* history.c */
char *get_file_history(info_t *info);
int write_history(info_t *info);
int read_file_history(info_t *info);
int add_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* list.c */
list_t *add_start_node(list_t **, const char *, int);
list_t *add_end_node(list_t **, const char *, int);
list_t *node_starts_with(list_t *, char *, char);
size_t print_str_list(const list_t *);
int delete_node_index(list_t **, unsigned int);
void free_node_list(list_t **);

/* list_handlers.c */
size_t list_length(const list_t *);
char **list_return_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);

/* main.c */
int main(int argc, char **argv);

/* memory_.c */
int pfree(void **);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_characters(char *, int, int);
char *locate_path(info_t *, char *, char *);

/* real_log.c */
char *_memset(char *, char, unsigned int);
void sfree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell_loop.c */
int hsh(info_t *, char **);
int find_in_built(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts(const char *, const char *);
char *_strcat(char *, char *);

/* string_handlers.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _put(char *);
int _putchar(char);

/* token.c */
char **string_words(char *, char *);
char **string_words1(char *, char);

/* variables.c */
info_t chain_delimiter(info_t *, char *, size_t *);
void chain_status(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_vars(info_t *);
int substitute_string(char **, char *);

#endif
