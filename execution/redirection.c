#include "../minishell.h"


int ft_which_redirection(char *redirection, char *file_name, t_quots *quots, t_env *envp)
{
    if (redirection[0] == '>' && redirection[1] == '>')
    {
        if ((ft_handle_append(file_name)) == -1)
            return (-1);
    }
    else if (redirection[0] == '<' && redirection[1] == '<')
    {
        dup2(quots->saved_stdin, STDIN_FILENO);
        if ((ft_handle_heredoc(file_name, envp, quots)) == -1)
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
// int check_handle_redirections(t_data *data, t_quots *quots, t_env *envp)
// {
//     int j;
//     char *arg;
//     char *join;

//     j = 0;
//     while (data->redirection[j])
//     {     
//         if (data->redirection[j + 1] == NULL)
//         {
//             ft_putstr_fd("ambiguous redirect\n");
//             exit_code = 1;
//             return(1);
//         }
//         if (ft_which_redirection(data->redirection[j], data->redirection[j + 1], quots, envp) == -1)
//         {
//             exit_code = 1;
//             return (1);
//         }
//         j+=2;
//     }
//     return(0);
// }
