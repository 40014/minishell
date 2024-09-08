#include "../minishell.h"

int check_if_contain_redirections(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '>' || cmd[i] == '<')
            return (1);
        i++;
    }
    return (0);
}
int check_if_redirection_end(char *argumment)
{
    int i;

    i = 0;
    while (argumment[i])
        i++;
    if (argumment[i - 1] == '>' || argumment[i - 1] == '<')
        return (1);
    return (0);
}
int check_if_contain_only_redirection(char *cmd)
{
    if (cmd[0] == '>' && cmd[1] == '\0')
        return (1);
    else if (cmd[0] == '<' && cmd[1] == '\0')
        return (2);
    else if (cmd[0] == '>' && cmd[1] == '>' && cmd[2] == '\0')
        return (3);
    else if (cmd[0] == '<' && cmd[1] == '<' && cmd[2] == '\0')
        return (4);
    return (0);
}

char *ft_cpy_commande(char *argumment, int i)
{
    char *commande;
    int l;

    l = i;
    while (argumment[l] && argumment[l] != '>' && argumment[l] != '<')
        l++;
    commande = malloc(l + 1);
    l = 0;
    while (argumment[i] && argumment[i] != '>' && argumment[i] != '<')
        commande[l++] = argumment[i++];
    commande[l] = '\0';
    return (commande);
}

int free_and_shift(char **argumment, int j)
{
    int k;

    free(argumment[j]);
    k = j;
    while (argumment[k])
    {
        argumment[k] = argumment[k + 1];
        k++;
    }
    j--;
    return (j);
}