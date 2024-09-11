#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
# include <fcntl.h>
#include <errno.h>


# define BUFFER_SIZE 1

typedef struct data
{
    char **argumment;
    struct data *next;
} t_data;

typedef struct env_var
{
    char *var;
    char *val;
    struct env_var *next;

} t_env;

typedef struct quot
{
    int x;
    int empty;
} t_quots;

typedef struct hold
{
    char *input;
    char *temp;
    int saved_stdin;

} t_hold;

typedef struct parser
{
    char *input;
    char *buffer;
    int buf_index;
    int i;
    char quote;
    t_env *env_var;
    t_quots *quots;
    char **args;
    int j;
} t_ParserState;

extern int exit_code;

char *replace_env_variable(const char *str, int *skip);
char *ft_environment_variables(char *arguments, t_env *env_var, t_quots *quots);
void finalize_args(t_ParserState *state);
void add_buffer_to_args(t_ParserState *state);
void handle_empty_argument(t_ParserState *state);
void init_parser_state(t_ParserState *state, char *input, t_env *env_var, t_quots *quots);
char *ft_environment_variables(char *arguments, t_env *env_var, t_quots *quots);
char *replace_env_variable(const char *str, int *skip);
void handle_dollar_sign(t_ParserState *state);
void handle_quotes(t_ParserState *state);
int handle_consecutive_quotes(t_ParserState *state);
char handle_quote(char current_char, char quote);
char	*ft_itoa(int n);
char *ft_strjoine(char const *s1, char const *s2);
int ft_skip_space(char c);
int	check_redirections(char *input);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strdup(const char *s1);
char    *ft_strjoinee(char *s1, const char *s2);
int     ft_is_valid(char c);
int     ft_is_digits(char c);
size_t  ft_strlen(const char *s);
void    ft_free_list(t_data *head);
int parse_line(t_data **data, char *input, t_env *env_var,t_quots *quots);
char **split_line_to_args(char *input, t_env *env_var, t_quots *quots);
char    *strsplit_by_pipe(char **str);
int     ft_count_args(char *input);
void    ft_add_node(t_data **head, char **arguments);
t_data  *creat_node(char **arguments);
int     check_qout(char *input);
void    exec_commandes(t_data *commandes, t_env **envp, t_data **data, t_hold **hold_vars);
int    exec_echo(char **commande);
void    ft_putstr(char *str);
int    exec_cd(char **commande, t_env *envp);
int    exec_pwd(char **commande);
char    *print_prompt(t_env *envp, char *hold, char *temp);
char    *ft_getenv(t_env *envp, char *var);
char    *ft_strjoin(char const *s1, char const *s2, int flag, int size);
int     ft_strcmp(char *s1, char *s2);
t_env   *env_to_list(char **envp);
t_env   *ft_one_node(char *envp);
char    *grep_env_value(char *envp, int i);
void    ft_free_list2(t_env *head);
int    exec_export(char **commande, t_env **envp);
int    exec_env(char **commande, t_env *envp);
void    ft_print_env(t_env *envp);
t_env   *ft_one_node2(char *envp);
int     ft_update_val(t_env **envp, char *var, char *val);
int    exec_unset(char **commande, t_env **envp);
int    exec_exit(char **commande, t_env **envp, t_data **data, t_hold **hold_vars);
int     ft_isalpha(int c, int i);
char    *remove_plus(char *var);
int     ft_contain_plus(char *commande);
int     check_argument(char *commande);
int     ft_strcmp2(char *s1, char *s2);
int    exec_non_builtin(char **comande, t_env **envp, t_data **data, t_hold **hold_vars);
char    **ft_split(char const *s, char c);
void    exec_with_pipes(t_env **envp, t_data **data, t_hold **hold_vars);
int    exec_simple_commande(char **argumment, t_env **envp, t_data **data, t_hold **hold_vars);
void	ft_putstr_fd(char const *str);
void ft_print_in_stderr(char *s1, char *s2, char *s3);
void ft_free_arr(char **paths);
void	ft_bzero(void *s, size_t n);
int	ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
int check_handle_redirections(char **argumment, int saved_stdin);
int check_if_contain_redirections(char *cmd);
int check_if_contain_only_redirection(char *cmd);
char *ft_cpy_commande(char *argumment, int i);
int ft_handle_output(char *argument, int i);
int ft_handle_input(char *argument, int i);
int ft_handle_append(char *argument, int i);
int free_and_shift(char **argumment, int j);
int check_if_redirection_end(char *argumment);

#endif