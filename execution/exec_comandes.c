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

int exec_simple_commande(t_data *commande, t_env **envp, t_data **data, t_hold **hold_vars)
{
    if (check_handle_redirections(commande->redirection, (*hold_vars)->saved_stdin, *envp) == 1)
        return (exit_code);
    if (ft_strcmp(commande->argumment[0], "echo") == 0)
        exit_code = exec_echo(commande->argumment);
    else if (ft_strcmp(commande->argumment[0], "pwd") == 0)
        exit_code = exec_pwd(commande->argumment);
    else if (ft_strcmp(commande->argumment[0], "cd") == 0)
        exit_code = exec_cd(commande->argumment, *envp);
    else if (ft_strcmp(commande->argumment[0], "export") == 0)
        exit_code = exec_export(commande->argumment, envp);
    else if (ft_strcmp(commande->argumment[0], "env") == 0)
        exit_code = exec_env(commande->argumment, *envp);
    else if (ft_strcmp(commande->argumment[0], "unset") == 0)
        exit_code = exec_unset(commande->argumment, envp);
    else if (ft_strcmp(commande->argumment[0], "exit") == 0)
        exit_code = exec_exit(commande->argumment, envp, data, hold_vars);
    else
        exit_code = exec_non_builtin(commande->argumment, envp, data, hold_vars);
    return (exit_code);
}

void exec_commandes(t_env **envp, t_data **data, t_hold **hold_vars)
{
    if ((*data)->next == NULL && (*data) != NULL)
        exec_simple_commande((*data), envp, data, hold_vars);
    else if ((*data)->next != NULL)
        exec_with_pipes(envp, data, hold_vars);
}