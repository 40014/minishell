NAME = minishell

PARSING =	main.c parsing/utils_expansion.c                              \
			parsing/handle_pip.c parsing/arg_parser.c                      \
			parsing/ft_checkers.c parsing/parser_utils.c                    \
			parsing/expansion.c parsing/checker_expansion.c                  \
			parsing/redirection_utils.c parsing/syntax_error.c  		      \
			parsing/utils.c  parsing/ft_free.c parsing/parsing.c 			   \
			parsing/utils_expansion1.c parsing/expansion_herdoc.c 				\
			parsing/ft_arg_to_node.c parsing/str_split.c parsing/herdoc_errors.c \
			parsing/redirection_list.c \
			
EXECUTION =	execution/exec_env.c execution/exec_unset.c                 \
			execution/prompt_utils.c execution/exec_cd.c                 \
			execution/exec_comandes.c execution/exec_exit.c               \
			execution/env_to_list.c execution/exec_export.c                \
			execution/exec_redirections.c  execution/redirection.c          \
			execution/exec_non_builtin_utils.c execution/set_shlvl.c         \
			execution/exec_non_builtin.c execution/exec_with_pipes.c          \
			execution/get_next_line_utils.c execution/get_next_line.c          \
			execution/exec_export_utils.c execution/printin_stderror.c          \
			execution/exec_echo.c execution/exec_pwd.c  execution/print_export.c \
			
			
CFLAGS = -Wall -Wextra -Werror -w -fsanitize=address 

all: $(NAME)

$(NAME): $(PARSING) $(EXECUTION) 
	cc $(CFLAGS) $(PARSING) $(EXECUTION) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

