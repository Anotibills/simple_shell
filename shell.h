#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

/* for read/write buff */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* 1 if using sys getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

/* for cmd chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

extern char **environ;

/**
 * struct lstr - function for singly linked list
 * @num: number to field
 * @str: string length
 * @next: pointer to the next node
 */
typedef struct lstr
{
	int num;
	char *str;
	struct lstr *next;
} list_t;

/**
 * struct psinfo - function containing pseudo-arguements
 * @arg: getline strings containing arguments
 * @argv: array of strings from arguments
 * @argc: an argument count
 * @path: path of string for cur cmd
 * @line_count: error count
 * @linecount_flag: if on, count this line of input
 * @err_num: error code for exit
 * @env: environ of linked list
 * @environ: modified copy of environ from env
 * @alias: alias node
 * @history: history node
 * @env_changed: on, if environ was changed
 * @status: status of result of the last command executed
 * @cmd_buff: pointer of address to cmd_buf, on if chaining
 * @cmd_buff_type: CMD_type ||, &&, ;
 * @fname: filename of program
 * @readfd: fd from which to read line input
 * @histcount: history line number count
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

        char **cmd_buff;
	int cmd_buff_type;
	int histcount;
	int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - function that contains a builtin string
 *@type: pointer to builtin command flag
 *@func: pointer to function
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;
/*toem_builtin.c*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/*toem_atoi.c*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*toem_builtin1.c*/
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_shloop.c*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void fork_cmd(info_t *);
void find_cmd(info_t *);

/*loophsh.c*/
int loophsh(char **);

/*toem_string.c*/
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);

/*toem_string1.c*/
void _puts(char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);


/*toem_shloop.c*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*toem_parser.c*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*loophsh.c*/
int loophsh(char **);

/*toem_error.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*toem_strings.c*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*toem_strings1.c*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*toem_realloc.c*/
char *_memset(char *, char, unsigned int);
void ifree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*toem_memory.c*/
int bfree(void **);

/*toem_error1.c*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*toem_getline.c*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*toem_getinfo.c*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*toem_environ.c*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/*toem_getenv.c*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*toem_history.c*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buff, int linecount);
int renumber_history(info_t *info);

/*toem_lists.c*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*toem_lists1.c*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*toem_vars.c*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/*toem_tokenizer.c*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/*toem_exit.c*/
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
#endif
