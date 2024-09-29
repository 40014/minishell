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
# include <signal.h>


# define BUFFER_SIZE 1

typedef struct redir_node
{
    char *redirection;
    struct redir_node *next;

} t_redir_node;

typedef struct data
{
    char    **argumment;
    t_redir_node *redirections;
    //char    **redirection;
    struct data *next;

} t_data;

typedef struct arg_node
{
    char *arg;
    struct arg_node *next;

} t_arg_node;

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
    int herdoc_expan;
    int saved_stdin;
} t_quots;

typedef struct hold
{
    char *input;
    char *temp;
} t_hold;

typedef struct parser
{
    char *input;
    char *buffer;
    int buf_index;
    int find_red;
    int i;
    char quote;
    t_env *env_var;
    t_quots *quots;
    char **args;
    char **redirections;
    int j;
    int redir_index;
    int flag_backslash;
} t_ParserState;

extern int exit_code;

void append_redir_node(t_redir_node **redir_list, t_redir_node *new_node);
int check_herdoc_error(char *input);
char    **split_string(const char* input);
void free_arg_list(t_arg_node *head);
t_arg_node *create_arg_node(char *arg);
void append_arg_node(t_arg_node **head, t_arg_node *new_node);
int count_arg_nodes(t_arg_node *head);
char **convert_list_to_array(t_arg_node *head);
int ft_skip_spaces_and_check_pipe(char *input, int *i);
void    ft_check_expansion_herdoc(char *input, t_quots *quots);
int ft_count_redirections(char *input);
void ft_printf_error(int i);
char    *ft_expand_herdoc(char  *str, t_env *env_var, t_quots *quots);
int	check_prompt(char *input);
char ft_handle_quote(char current_chara, char quotee);
char *replace_env_variable(const char *str, int *skip);
char *ft_environment_variables(char *arguments, t_env *env_var, t_quots *quots);
void finalize_args(t_ParserState *state, t_arg_node **arg_list, t_redir_node **redir_list);
//void finalize_args(t_ParserState *state, t_arg_node **arg_list);
void add_buffer_to_args(t_ParserState *state, t_arg_node **arg_list,  t_redir_node **redir_list);
//void add_buffer_to_args(t_ParserState *state, t_arg_node **arg_list);
void handle_empty_argument(t_ParserState *state, t_arg_node *arg_list);
void init_parser_state(t_ParserState *state, char *input, t_env *env_var, t_quots *quots);
char *ft_environment_variables(char *arguments, t_env *env_var, t_quots *quots);
void handle_dollar_sign(t_ParserState *state, t_arg_node **arg_list, t_redir_node **redir_list);
//void handle_dollar_sign(t_ParserState *state, t_arg_node **arg_list);
void handle_quotes(t_ParserState *state);
int handle_consecutive_quotes(t_ParserState *state);
char	*ft_itoa(int n);
int ft_skip_space(char c);
int check_errors(char *input);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strdup(const char *s1);
char    *ft_strjoinee(char *s1, const char *s2);
int     ft_is_valid(char c);
int     ft_is_digits(char c);
size_t  ft_strlen(const char *s);
void    ft_free_list(t_data *head);
int parse_line(t_data **data, char *input, t_env *env_var,t_quots *quots);
char **split_line_to_args(char *input, t_env *env_var, t_quots *quots, t_redir_node **redir_list);
//char **split_line_to_args(char *input, t_env *env_var, t_quots *quots, char ***redirections);
char    *strsplit_by_pipe(char **str);
int     ft_count_args(char *input);
void ft_add_node(t_data **head, char **arguments, t_redir_node *redirection);
t_data *creat_node(char **arguments, t_redir_node *redirection);
t_redir_node *create_redir_node(char *redir);
// void ft_add_node(t_data **head, char **arguments, char **redirection);
//t_data *creat_node(char **arguments, char **redirection);
void exec_commandes(t_env **envp, t_data **data, t_hold **hold_vars, t_quots *quots);
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
void exec_with_pipes(t_env **envp, t_data **data, t_hold **hold_vars, t_quots *quots);
int exec_simple_commande(t_quots *quots, t_env **envp, t_data **data, t_hold **hold_vars);
void	ft_putstr_fd(char const *str);
void ft_print_in_stderr(char *s1, char *s2, char *s3);
void ft_free_arr(char **paths);
void	ft_bzero(void *s, size_t n);
int	ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
int check_handle_redirections(t_data *data, t_quots *quots, t_env *envp);
int ft_handle_output(char *file_name);
int ft_handle_append(char *file_name);
int ft_handle_input(char *file_name);
int ft_handle_heredoc(char *delimiter, t_env *envp, t_quots *quots);
char *set_shlvl(char *var, char *shlvl);
int ft_strcmp3(char *s1, char *s2);
int	ft_atoi(char *str);
void ft_print_env2(t_env *envp);
char **convert_envp_to_arr(t_env *envp);
void handlle_sigint(int sig);

#endif