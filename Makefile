NAME	=	minishell

PARSING	=	parsing/redirection_list.c                                   \
			main.c parsing/utils_expansion.c                              \
			parsing/handle_pip.c parsing/arg_parser.c                      \
			parsing/ft_checkers.c parsing/parser_utils.c                    \
			parsing/expansion.c parsing/checker_expansion.c                  \
			parsing/arg_parser_utils.c parsing/parser_utils1.c                \
			parsing/redirection_utils.c parsing/syntax_error.c  		       \
			parsing/utils.c  parsing/ft_free.c parsing/parsing.c 			    \
			parsing/utils_expansion1.c parsing/expansion_herdoc.c 				 \
			parsing/syntax_errors_utils.c parsing/utils_expansion2.c              \
			parsing/redirection_condition.c parsing/redirection_condition1.c       \
			parsing/expansion2.c  parsing/expansion3.c parsing/str_split_utils.c    \
			parsing/ft_arg_to_node.c parsing/str_split.c parsing/herdoc_errors.c     \
			
EXECUTION =	execution/exec_non_builtin.c execution/exec_with_pipes.c                   \
			execution/env_to_list.c execution/built_ins/exec_export.c                   \
			execution/get_next_line_utils.c execution/get_next_line.c                    \
			execution/built_ins/print_export.c execution/exec_heredocs.c                  \
			execution/built_ins/exec_echo.c execution/built_ins/exec_pwd.c                 \
			execution/built_ins/exec_env.c execution/built_ins/exec_unset.c                 \
			execution/exec_non_builtin_utils.c execution/built_ins/set_shlvl.c               \
			execution/built_ins/exec_export_utils.c execution/printin_stderror.c              \
			execution/exec_comandes.c execution/built_ins/exec_exit.c execution/split.c        \
			execution/exec_redirections.c execution/redirection.c execution/main_utils.c        \
			execution/prompt_utils.c execution/built_ins/exec_cd.c execution/env_to_list_utils.c \

			
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g3

all: $(NAME)

$(NAME) : $(PARSING) $(EXECUTION)
	cc $(CFLAGS) $(PARSING) $(EXECUTION) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all
