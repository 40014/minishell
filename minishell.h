#ifndef MINISHELL_H
# define    MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct echo
{
    char    **argumment;
    char    *command;
    char    *options;
    struct data *next;
}   t_data;

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int	ft_count_args(char *input);
void	ft_add_node(t_data **head, char *command, char **arguments);
t_data *creat_node(char *command, char **arguments);
char *strsplit_by_pipe(char **str);

#endif