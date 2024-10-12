#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 1
# define PATH_MAX 4096

typedef struct redir_node
{
	char				*redirection;
	struct redir_node	*next;

}						t_redir_node;

typedef struct data
{
	char				**argumment;
	t_redir_node		*redirections;
	struct data			*next;

}						t_data;

typedef struct arg_node
{
	char				*arg;
	struct arg_node		*next;

}						t_arg_node;

typedef struct env_var
{
	char				*var;
	char				*val;
	struct env_var		*next;

}						t_env;

typedef struct quot
{
	int					x;
	int					empty;
	int					herdoc_expan;
	int					id;
	int					fdin;
	int					fdout;
}						t_quots;

typedef struct hold
{
	char				*input;
	char				*temp;
}						t_hold;

typedef struct parser
{
	char				*input;
	char				*buffer;
	int					buf_index;
	int					find_red;
	int					i;
	char				quote;
	t_env				*env_var;
	t_quots				*quots;
	char				**args;
	char				**redirections;
	int					j;
	int					redir_index;
	int					flag_backslash;
	int					check_last_space;
	int					check_first_space;
}						t_ParserState;

typedef struct hold_main
{
	t_data				*data;
	t_env				*env_var;
	t_hold				*hold_vars;
	t_quots				quots;
	char				*input;
	int					i;
	int					saved_stdout;
	int					saved_stdin;
	char				*temp;
}						t_hold_main;

typedef struct ParserContext
{
	t_ParserState		*state;
	t_arg_node			**arg_list;
	t_redir_node		**redir_list;
	int					check;
	int					j;

}						t_ParserContext;

extern int				exit_code;

int						ft_handle_dollar_herdoc(char c,
							t_redir_node **redir_list);
void					free_env_if_needed(char *env);
void					handle_redirection_buffer_or_condition(t_ParserContext *context,
							t_ParserState *state, char **result);
void					handle_redirection_input_condition(t_ParserContext *context,
							t_ParserState *state, char **result);
void					handle_redirection_last_space(t_ParserContext *context,
							t_ParserState *state, char *result);
void					copy_to_buffer(t_ParserState *state, char *source);
void					handle_empty_redirection(t_ParserContext *context,
							t_ParserState *state);
void					handle_redirection_condition_3(t_ParserContext *context,
							t_ParserState *state, char **result);
void					handle_redirection_condition_2(t_ParserContext *context,
							t_ParserState *state);
void					handle_redirection_condition_1(t_ParserContext *context,
							t_ParserState *state);
void					process_redirection(t_ParserContext *context,
							t_ParserState *state, char **result, char *env);
void					process_arg_node(t_ParserContext *context,
							t_ParserState *state, char **result, char *env);
int						ft_handle_pipe(char *input, int *i);
int						ft_handle_redirection(char *input, int *i);
void					handle_empty_argument_backslash(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
int						is_next_char_not_squote_or_null(t_ParserState *state,
							int index);
int						is_next_char_not_dquote_or_null(t_ParserState *state,
							int index);
int						is_next_char_space_or_null(t_ParserState *state,
							int index);
int						is_special_char(char c);
void					process_buffer_until_special_char(t_ParserState *state);
int						handle_errors(char *input);
int						ft_check(char *input);
int						handle_allocation_error(char **result, int idx);
int						allocate_and_store_word(char **result, int idx,
							const char *start, int len);
int						count_results(char **result);
t_ParserContext			initialize_parser_context(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
void					handle_null_env_or_redir(t_ParserContext *context,
							char *env, int check, int i);
void					free_env_result(char **env, char **result, int i,
							int check);
void					free_split_string(char **words);
char					*handle_env_variable(t_ParserState *state);
int						handle_split_env_result(t_ParserState *state,
							t_arg_node **arg_list, char **result, int *check);
void					append_redir_node(t_redir_node **redir_list,
							t_redir_node *new_node);
int						check_herdoc_error(char *input);
char					**split_string(const char *input, t_ParserState *state);
void					free_arg_list(t_arg_node *head);
t_arg_node				*create_arg_node(char *arg);
void					append_arg_node(t_arg_node **head,
							t_arg_node *new_node);
int						count_arg_nodes(t_arg_node *head);
char					**convert_list_to_array(t_arg_node *head);
int						ft_skip_spaces_and_check_pipe(char *input, int *i);
void					ft_check_expansion_herdoc(char *input, t_quots *quots);
int						ft_count_redirections(char *input);
void					ft_printf_error(int i);
char					*ft_expand_herdoc(char *str, t_env *env_var,
							t_quots *quots);
int						check_prompt(char *input);
char					ft_handle_quote(char current_chara, char quotee);
char					*replace_env_variable(const char *str, int *skip);
char					*ft_environment_variables(char *arguments,
							t_env *env_var, t_quots *quots);
void					finalize_args(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
// void finalize_args(t_ParserState *state, t_arg_node **arg_list);
void					add_buffer_to_args(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
// void add_buffer_to_args(t_ParserState *state, t_arg_node **arg_list);
void					handle_empty_argument(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
void					init_parser_state(t_ParserState *state, char *input,
							t_env *env_var, t_quots *quots);
char					*ft_environment_variables(char *arguments,
							t_env *env_var, t_quots *quots);
void					handle_dollar_sign(t_ParserState *state,
							t_arg_node **arg_list, t_redir_node **redir_list);
// void handle_dollar_sign(t_ParserState *state, t_arg_node **arg_list);
void					handle_quotes(t_ParserState *state);
int						handle_consecutive_quotes(t_ParserState *state);
char					*ft_itoa(int n);
int						ft_skip_space(char c);
int						check_errors(char *input);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strdup(const char *s1);
char					*ft_strjoinee(char *s1, const char *s2);
int						ft_is_valid(char c);
int						ft_is_digits(char c);
size_t					ft_strlen(const char *s);
void					ft_free_list(t_data *head);
int						parse_line(t_data **data, char *input, t_env *env_var,
							t_quots *quots);
char					**split_line_to_args(char *input, t_env *env_var,
							t_quots *quots, t_redir_node **redir_list);
// char **split_line_to_args(char *input, t_env *env_var, t_quots *quots,
// char ***redirections);
char					*strsplit_by_pipe(char **str);
void					ft_add_node(t_data **head, char **arguments,
							t_redir_node *redirection);
t_data					*creat_node(char **arguments,
							t_redir_node *redirection);
t_redir_node			*create_redir_node(char *redir);
// void ft_add_node(t_data **head, char **arguments, char **redirection);
// t_data *creat_node(char **arguments, char **redirection);
void					exec_commandes(t_env **envp, t_data **data,
							t_hold **hold_vars, t_quots *quots);
int						exec_echo(char **commande);
void					ft_putstr(char *str);
int						exec_cd(char **commande, t_env **envp, int check,
							int wd_err);
int						exec_pwd(char **commande, t_env *envp);
char					*print_prompt(t_env *envp);
char					*ft_getenv(t_env *envp, char *var);
char					*ft_strjoin(char const *s1, char const *s2, int flag,
							int size);
int						ft_strcmp(char *s1, char *s2);
t_env					*env_to_list(char **envp, char *first_arg);
t_env					*ft_one_node(char *envp);
char					*grep_env_value(char *envp, int i);
void					ft_free_list2(t_env *head);
int						exec_export(char **commande, t_env **envp);
int						exec_env(char **commande, t_env *envp);
void					ft_print_env(t_env *envp);
t_env					*ft_one_node2(char *envp);
int						ft_update_val(t_env **envp, char *var, char *val);
int						exec_unset(char **commande, t_env **envp);
int						exec_exit(char **commande, t_env **envp, t_data **data,
							t_hold **hold_vars);
int						ft_isalpha(int c, int i);
char					*remove_plus(char *var);
int						ft_contain_plus(char *commande);
int						check_argument(char *commande);
int						ft_strcmp2(char *s1, char *s2);
int						exec_non_builtin(char **comande, t_env **envp);
char					**ft_split(char const *s, char c);
void					exec_with_pipes(t_env **envp, t_data **data,
							t_hold **hold_vars, t_quots *quots);
int						exec_simple_commande(t_env **envp, t_data **data,
							t_hold **hold_vars);
void					ft_putstr_fd(char const *str);
void					ft_print_in_stderr(char *s1, char *s2, char *s3);
void					ft_free_arr(char **paths);
void					ft_bzero(void *s, size_t n);
int						ft_strchr(const char *s, int c);
void					*ft_calloc(size_t count, size_t size);
char					*get_next_line(int fd);
int						check_handle_redirections(t_data *data);
int						ft_handle_output(char *file_name);
int						ft_handle_append(char *file_name);
int						ft_handle_input(char *file_name);
int						ft_handle_heredoc(char *delimiter, t_env *envp,
							t_quots *quots);
char					*set_shlvl(char *var, char *shlvl, char *newshlvl);
int						ft_strcmp3(char *s1, char *s2);
int						ft_atoi(char *str);
int						ft_print_export(t_env *envp);
char					**convert_envp_to_arr(t_env *envp);
void					handlle_sigint(int sig);
int						ft_exec_heredocs(t_data **data_add, t_env *envp,
							t_quots *quots);
void					add_update_last_commande(t_env **env, char *var_val);
void					add_missing_vars(t_env **env, int t1, int t2, int t3);
void					free_before_exit(t_hold **hold_vars, t_env **envp,
							t_data **data, int i);
int						if_contain_directory(char *commande);
int						count_nodes(t_env *envp);
void					ft_create_nodes(t_env **head, char *envp);
void					check_if_directory(char *path);
int						ft_find_del(char *line, char *del);
void					delete_heredoc_files(void);

#endif