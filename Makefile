NAME = minishell

SOURCE = main.c utils.c ft_split.c

CFLAGS = -Wall -Wextra -Werror -w

all: $(NAME)

$(NAME): $(SOURCE)
	cc $(CFLAGS) $(SOURCE) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all