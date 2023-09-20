#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @reg_inpute: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *reg_inpute;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} d_sh;

/**
 * struct seperate_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct seperate_list_s
{
	char separator;
	struct seperate_list_s *next;
} seperate_list;

/**
 * struct ln_ls_s - single linked list
 * @line: command line
 * @next: next node
 * Description: THIS IS A single linked
 * list tHAT WILL BE USED TO store command lines
 */
typedef struct ln_ls_s
{
	char *line;
	struct ln_ls_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct all_builtin_s - all_builtin struct for command args.
 * @name: The name of the command all_builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct all_builtin_s
{
	char *name;
	int (*f)(d_sh *data_shell);
} all_builtin_t;

/* aux_lists.c */
seperate_list *put_seperate_list(seperate_list **head, char sep);
void free_seperate_list(seperate_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *addtion_of_reverseNode(r_var **head, int lvar, char *var, int lval);
void empty_of_reverselist(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *first_point, const void *pointerr, unsigned int size);
void *_realloc(void *pointerr, unsigned int first_size, unsigned int sec_size);
char **allo_dp(char **pointerr, unsigned int first_size, unsigned int sec_size);

/* aux_str2.c */
char *string_dup(const char *s);
int _strlen(const char *s);
int comp_char(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void reverse_str(char *s);

/* check_syntax_error.c */
int rep_string(char *reg_inpute, int i);
int find_synt_err(char *reg_inpute, int i, char last);
int first_char(char *reg_inpute, int *i);
void write_synt_err(d_sh *data_shell, char *reg_inpute, int i, int bool);
int check_syntax_error(d_sh *data_shell, char *reg_inpute);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(d_sh *data_shell);

/* call_lines.c */
char *call_lines(int *i_eof);

/* split.c */
char *swap_some_characters(char *reg_inpute, int bool);
void add_separators(seperate_list **head_s, line_list **head_l, char *reg_inpute);
void go_next(seperate_list **list_s, line_list **list_l, d_sh *data_shell);
int divide_the_comad_exec(d_sh *data_shell, char *reg_inpute);
char **split_line(char *reg_inpute);

/* rep_var.c */
void check_env(r_var **h, char *in, d_sh *data);
int check_vars(r_var **h, char *in, char *st, d_sh *data);
char *replaced_reg_inpute(r_var **head, char *reg_inpute, char *first_reg_inpute, int nlen);
char *rep_var(char *reg_inpute, d_sh *data_shell);

/* get_line.c */
void get_lines(char **linepointerr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **linepointerr, size_t *n, FILE *stream);

/* is_execute */
int is_execute(d_sh *data_shell);

/* comand_exec.c */
int is_change_dir(char *path, int *i);
char *comad_loc(char *comad_exec, char **_environ);
int is_chmod(d_sh *data_shell);
int chk_err_comad(char *dir, d_sh *data_shell);
int comand_exec(d_sh *data_shell);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(d_sh *data_shell);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, d_sh *data_shell);
int _setenv(d_sh *data_shell);
int _unsetenv(d_sh *data_shell);

/* cd.c */
void cdir_prev_dir(d_sh *data_shell);
void cd_to(d_sh *data_shell);
void cdir_prev(d_sh *data_shell);
void cdir_home(d_sh *data_shell);

/* cdir_shell.c */
int cdir_shell(d_sh *data_shell);

/* get_all_builtin */
int (*get_all_builtin(char *comad_exec))(d_sh *data_shell);

/* _exit.c */
int dismiss_shell(d_sh *data_shell);

/* aux_stdlib.c */
int getLength(int n);
char *aid_func(int n);
int func(char *s);

/* aux_error1.c */
char *strcat_cd(d_sh *, char *, char *, char *);
char *error_get_cd(d_sh *data_shell);
char *error_not_found(d_sh *data_shell);
char *shell_err(d_sh *data_shell);

/* aux_error2.c */
char *error_get_alias(char **args);
char *err_ver(d_sh *data_shell);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(d_sh *data_shell);


/* get_err.c */
int get_err(d_sh *data_shell, int eval);

/* get_signt.c */
void get_signt(int sig);

/* aid_assist.c */
void aid_free_ver(void);
void aid_assist_setenv(void);
void aid_assist_unsetenv(void);
void aid_assist_all(void);
void aid_assist_dismiss(void);

/* aid_assist2.c */
void aid_assist(void);
void aid_assist_alias(void);
void aid_assist_cd(void);

/* gassist.c */
int gassist(d_sh *data_shell);

#endif
