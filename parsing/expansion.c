#include "../minishell.h"

char *replace_env_variable(const char *str, int *skip)
{
    char var_name[BUFSIZ];
    int var_index;
    char *env;
    char *result;

    var_index = 0;

    if (str[*skip] == '$')
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    while (str[*skip] && (isalnum(str[*skip]) || str[*skip] == '_'))
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    var_name[var_index] = '\0';
    return (var_name);
}

void append_char_to_result(char **result, char arguments_char)
{
    char str[2];

    str[0] = arguments_char;
    str[1] = '\0';
    *result = ft_strjoinee(*result, str);
}

char *handle_dollar_sign_in_arguments(char *arguments, t_env *env_var, int *i, t_quots *quots)
{
    char    tmp[BUFSIZ];
    char    *env;
    int j;

    j = 0;
    (*i)++;
    while (arguments[*i] != '\0' && arguments[*i] != ' ' && ft_is_valid(arguments[*i]) == 1 &&
     arguments[*i] != '$' && j < sizeof(tmp) - 1)
    {
        tmp[j] = arguments[*i];
        j++;
        (*i)++;
    }
    tmp[j] = '\0';
    env = ft_getenv(env_var, tmp);
    return (env);
}

char *ft_environment_variables(char *arguments, t_env *env_var, t_quots *quots)
{
    int i;
    char *result;
    char *env_result;

    i = 0;
    result = NULL;
    while (arguments[i] != '\0')
    {
        if (arguments[i] == '$' && ft_is_digits(arguments[i + 1]) == 1)
            i = i + 2;
        else if (arguments[i] == '$' && arguments[i + 1] != '$' && (quots->x == 0 || quots->x == 2) && arguments[i + 1] != '\0')
        {
            env_result = handle_dollar_sign_in_arguments(arguments, env_var, &i, quots);
            if (env_result != NULL)
                result = ft_strjoinee(result, env_result);
        }
        else
        {
            append_char_to_result(&result, arguments[i]);
            i++;
        }
    }
    if (result == NULL)
        arguments = NULL;
    else
        arguments = result;
    quots->x = 0;
    return (arguments);
}
