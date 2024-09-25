#include "../minishell.h"

char *replace_env_variable(const char *str, int *skip)
{
    char var_name[BUFSIZ];
    int var_index;

    var_index = 0;
    if (str[*skip] == '$')
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    while (str[*skip] && ft_is_valid(str[*skip]) == 1)
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    var_name[var_index] = '\0';
    return (ft_strdup(var_name));
}
