#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (s1 == NULL || s2 == NULL)
        return (1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int exec_simple_commande(t_quots *quots, t_env **envp, t_data **data, t_hold **hold_vars)
{
    // if (check_handle_redirections(*data, quots, *envp) == 1)
    //     return (exit_code);
    if (ft_strcmp((*data)->argumment[0], "echo") == 0)
        exit_code = exec_echo((*data)->argumment);
    else if (ft_strcmp((*data)->argumment[0], "pwd") == 0)
        exit_code = exec_pwd((*data)->argumment);
    else if (ft_strcmp((*data)->argumment[0], "cd") == 0)
        exit_code = exec_cd((*data)->argumment, *envp);
    else if (ft_strcmp((*data)->argumment[0], "export") == 0)
        exit_code = exec_export((*data)->argumment, envp);
    else if (ft_strcmp((*data)->argumment[0], "env") == 0)
        exit_code = exec_env((*data)->argumment, *envp);
    else if (ft_strcmp((*data)->argumment[0], "unset") == 0)
        exit_code = exec_unset((*data)->argumment, envp);
    else if (ft_strcmp((*data)->argumment[0], "exit") == 0)
        exit_code = exec_exit((*data)->argumment, envp, data, hold_vars);
    else
        exit_code = exec_non_builtin((*data)->argumment, envp, data, hold_vars);
    return (exit_code);
}

void exec_commandes(t_env **envp, t_data **data, t_hold **hold_vars, t_quots *quots)
{
    if ((*data)->next == NULL && (*data) != NULL)
        exec_simple_commande(quots, envp, data, hold_vars);
    else if ((*data)->next != NULL)
        exec_with_pipes(envp, data, hold_vars, quots);
}