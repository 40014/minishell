#include "../minishell.h"

void ft_process_quote(char *input, int *i, char *quote)
{
    *quote = ft_handle_quote(input[*i], *quote);
    (*i)++;
}

void    ft_check_expansion_herdoc(char *input, t_quots *quots)
{
    int i;
    char    quote;

    i = 0;
    quote = 0;
    quots->herdoc_expan = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '\"')
            ft_process_quote(input, &i, &quote);
        else if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
        {
            i += 2;
            while (input[i] != '\0' && input[i] != '\'' && input[i] != '\"')
                i++;
            if (input[i] == '\'' || input[i] == '\"')
                quots->herdoc_expan = 1;
            if (input[i] == '\0')
                break;
        }
        else
            i++;
    }
}
