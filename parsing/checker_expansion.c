#include "../minishell.h"

void    ft_check_expansion_herdoc(char *input, t_env *env_var)
{
    int i;
    char    quote;

    i = 0;
    quote = 0;
    env_var->herdoc_expan = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            quote = ft_handle_quote(input[i], quote);
            i++;
        }
        else if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
        {
            i += 2;
            while (input[i] != '\0' && input[i] != '\'' && input[i] != '\"')
                i++;
            if (input[i] == '\'' || input[i] == '\"')
                env_var->herdoc_expan = 1;
            if (input[i] == '\0')
                break;
        }
        else
            i++;
    }

}
