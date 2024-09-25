#include "../minishell.h"

void append_char_to_result(char **result, char arguments_char)
{
    char str[2];

    str[0] = arguments_char;
    str[1] = '\0';
    *result = ft_strjoinee(*result, str);
}

char *handle_dollar_sign_in_arguments(char *arguments, t_env *env_var, int *i)
{
    char    tmp[BUFSIZ];
    char    *env;
    long unsigned int   j;

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

void ft_handle_digit_argument(char **result, int *i, char *arguments)
{
    if (arguments[*i + 1] == '0')
    {
        *result = ft_strjoinee(*result, "minishell");
        *i += 2;
    }
    else
        *i += 2;
}

void ft_finalize_arguments(char **arguments, char *result, t_quots *quots)
{
    if (result == NULL)
        *arguments = NULL;
    else
        *arguments = result;
    quots->x = 0;
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
            ft_handle_digit_argument(&result, &i, arguments);
        else if (arguments[i] == '$' && arguments[i + 1] != '$' && (quots->x == 0 || quots->x == 2) && arguments[i + 1] != '\0')
        {
            env_result = handle_dollar_sign_in_arguments(arguments, env_var, &i);
            if (env_result != NULL)
                result = ft_strjoinee(result, env_result);
        }
        else
        {
            append_char_to_result(&result, arguments[i]);
            i++;
        }
    }
    ft_finalize_arguments(&arguments, result, quots);
    return (arguments);
}

// char    *ft_expand_herdoc(char  *str, t_env *env_var)
// {
//     int i;
//     long unsigned int j;
//     char    *result;
//     char    *env_result;
//     char    tmp[BUFSIZ];
//     char character[2];

//     i = 0;
//     result = NULL;
//     while (str[i] != '\0')
//     {
//         if (str[i] == '$' && ft_is_digits(str[i + 1]) == 1 && env_var->herdoc_expan != 1)
//         {
//             if (str[i + 1] == '0')
//             {
//                 result = ft_strjoinee(result, "minishell");
//                 i += 2;
//             }
//             else
//                 i += 2;
//         }
//         else if (str[i] != '\0' && str[i] == '$' && str[i + 1] != '$' && env_var->herdoc_expan != 1)
//         {
//             i++;
//             j = 0;
//             while (str[i] != '\0' && str[i] != ' ' && str[i] != '$' && ft_is_valid(str[i]) == 1 && j < sizeof(tmp) - 1)
//             {
//                 tmp[j] = str[i];
//                 j++;
//                 i++;
//             }
//             tmp[i] = '\0';
//             env_result = ft_getenv(env_var, tmp);
//             if (env_result != NULL)
//                 result = ft_strjoinee(result, env_result);
//         }
//         else
//         {
//             character[0] = str[i];
//             character[1] = '\0';
//             result = ft_strjoinee(result, character);
//             i++;
//         }
//     }
//     if (result == NULL)
//         return (ft_strdup(str));
//     else
//         return (result);
// }
