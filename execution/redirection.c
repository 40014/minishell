#include "../minishell.h"


int ft_which_redirection(char *redirection, char *file_name, t_quots *quots, t_env *envp)
{
    if (redirection[0] == '>' && redirection[1] == '>')
    {
        if ((ft_handle_append(file_name)) == -1)
            return (-1);
    }
    else if (redirection[0] == '>')
    {
        if ((ft_handle_output(file_name)) == -1)
            return (-1);
    }
    else if (redirection[0] == '<')
    {
        if ((ft_handle_input(file_name)) == -1)
            return (-1);
    }
    return (0);
}

int check_handle_redirections(t_data *data, t_quots *quots, t_env *envp)
{
    t_redir_node *temp;

    temp = data->redirections;

    while (temp)
    {
        if (temp->next->redirection == NULL)
        {
            ft_putstr_fd("ambiguous redirect\n");
            exit_code = 1;
            return(1);
        }
        if (ft_which_redirection(temp->redirection, temp->next->redirection, quots, envp) == -1)
        {
            exit_code = 1;
            return (1);
        }
        temp = temp->next->next;
    }
    return(0);
}
