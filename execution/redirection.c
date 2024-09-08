#include "../minishell.h"


int ft_which_redirection(char *argumment, int i)
{
    if (argumment[i] == '>' && argumment[i + 1] == '>')
    {
        if ((i = ft_handle_append(argumment, i + 1)) == -1)
            return (-1);
    }
    else if (argumment[i] == '<' && argumment[i + 1] == '<')
    {
        if ((i = ft_handle_heredoc(argumment, i + 1)) == -1)
            return (-1);
    }
    else if (argumment[i] == '>')
    {
        if ((i = ft_handle_output(argumment, i)) == -1)
            return (-1);
    }

    else if (argumment[i] == '<')
    {
        if ((i = ft_handle_input(argumment, i)) == -1)
            return (-1);
    }
    return (i);
}

char *handle_redirections(char *argumment)
{
    char *commande;
    int i;

    i = 0;
    commande = NULL;
    exit_code = 0;
    if (argumment[i] != '>' && argumment[i] != '<')
        commande = ft_cpy_commande(argumment, 0);
    while (argumment[i])
    {
        while (argumment[i] != '>' && argumment[i] != '<')
            i++;
        i = ft_which_redirection(argumment, i);
        if (i == -1)
        {
            exit_code = 1;
            free(commande);
            return (NULL);
        }
        i++;
    }
    return (commande);
}
int handle_redirection_end(char **argumment, int j)
{
    int i;
    char *join;
    char *arg;

    join = ft_strjoin(argumment[j], argumment[j + 1], 1, 1);
    arg = handle_redirections(join);
    if (exit_code == 1)
    {
        free(join);
        return (-1);
    }
    if (arg != NULL)
    {
        free(argumment[j]);
        argumment[j] = arg;
        j = free_and_shift(argumment, j + 1);
    }
    else
    {
        j = free_and_shift(argumment, j);
        j = free_and_shift(argumment, j + 1);
    }
    free(join);
    return (j);
}
int check_handle_redirections(char **argumment)
{
    int j;
    char *arg;
    char *join;

    j = 0;
    while (argumment[j])
    {
        if (check_if_contain_only_redirection(argumment[j]) > 0)
        {
            join = ft_strjoin(argumment[j], argumment[j + 1], 1, 1);
            handle_redirections(join);
            if (exit_code == 1)
            {
                free(join);
                return (1);
            }
            j = free_and_shift(argumment, j);
            j = free_and_shift(argumment, j + 1);
            free(join);
        }
        else if ((check_if_contain_redirections(argumment[j])) == 1)
        {
            if (check_if_redirection_end(argumment[j]) == 1)
            {
                if ((j = handle_redirection_end(argumment, j)) == -1)
                    return (1);
            }
            else
            {
                arg = handle_redirections(argumment[j]);
                if (exit_code == 1)
                {
                    free(arg);
                    return (1);
                }
                if (arg != NULL)
                {
                    free(argumment[j]);
                    argumment[j] = arg;
                }
                else
                    j = free_and_shift(argumment, j);
            }
        }
        j++;
    }
}