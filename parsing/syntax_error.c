#include "../minishell.h"

int ft_check_unclosed_quote(int quote)
{
    if (quote != 0)
    {
        if (quote == '\'')
            return 2;
        else
            return 3;
    }
    return 0;
}

void ft_handle_quote_and_increment(char *input, int *i, int *quote)
{
    *quote = ft_handle_quote(input[*i], *quote);
    (*i)++;
}

int ft_handle_pipe(char *input, int *i)
{
    (*i)++;
    while (input[*i] != '\0' && ft_skip_space(input[*i]) == 1)
        (*i)++;
    if (input[*i] == '\0' || input[*i] == '|')
        return (1);
    return (0);
}

int ft_handle_redirection(char *input, int *i)
{
    if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
        (*i) += 2;
    else
        (*i)++;
    while (input[*i] != '\0' && ft_skip_space(input[*i]) == 1)
        (*i)++;
    if (input[*i] == '\0' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
        return (1);
    return (0);
}

int check_errors(char *input)
{
    int	i;
    int	quote;

	i = 0;
	quote = 0;
    if (ft_skip_spaces_and_check_pipe(input, &i) == 1)
        return 1;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '\"')
            ft_handle_quote_and_increment(input, &i, &quote);
        else if ((input[i] == '|' || input[i] == '>' || input[i] == '<') && quote == 0)
        {
            if (input[i] == '|')
            {
                if (ft_handle_pipe(input, &i) == 1)
                    return (1);
                continue;
            }
            if (ft_handle_redirection(input, &i) == 1)
                return (1);
        }
        else
            i++;
    }
    return (ft_check_unclosed_quote(quote));
}
