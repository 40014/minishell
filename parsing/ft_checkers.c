#include "../minishell.h"

int ft_skip_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
int	check_prompt(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		while ((input[i] == '\t' || input[i] == '\n' || input[i] == '\v' || input[i] == '\f' || input[i] == '\r' || input[i] == ' ') && (input[i] != '\0'))
			i++;
		if (input[i] == '\0')
			return (0);
		else 
			return (1);
	}
	return (0);
}
int ft_count_redirections(char *input)
{
    int i;
    int count;
    char quote;
	char file_quote;

    i = 0;
    count = 0;
    quote = 0;
	file_quote = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (quote == 0) 
                quote = input[i];
            else if (quote == input[i]) 
                quote = 0;
            i++;
        }
        else if ((input[i] == '>' || input[i] == '<') && quote == 0)
        {
            count++;
            if (input[i + 1] == '>' || input[i + 1] == '<')
                i += 2;
            else
                i++;
            while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
                i++;
            if (input[i] != '\0' && ft_skip_space(input[i]) == 0 && input[i] != '>' && input[i] != '<')
            {
                count++;
                if (input[i] == '\'' || input[i] == '"')
                {
                    file_quote = input[i];
                    i++;
                    while (input[i] != '\0' && input[i] != file_quote)
                        i++;
                    if (input[i] == file_quote)
                        i++;
                }
                else
                {
                    while (input[i] != '\0' && ft_skip_space(input[i]) == 0 && input[i] != '>' && input[i] != '<')
                        i++;
                }
            }
        }
        else
            i++;
    }
	printf("cound = %d\n", count);
    return (count);
}

int ft_count_args(char *input)
{
	int	count;
	int	i;
	char	quote;

	i = 0;
	quote = 0;
	count = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = ft_handle_quote(input[i], quote);
			i++;
		}
		else if (((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<')) && quote == 0)
		{
			count++;
			i += 2;
			while (ft_skip_space(input[i]) == 1)
				i++;
			if (input[i] != '\0' && ft_skip_space(input[i]) == 0)
			{
				count++;
				while (input[i] != '\0' && ft_skip_space(input[i]) == 0 && input[i] != '>' && input[i] != '<' && input[i] != '\'' && input[i] != '"')
					i++;
			}
		}
		else if ((input[i] == '>' || input[i] == '<') && quote == 0)
		{
			count++;
			i++;
			while (ft_skip_space(input[i]) == 1)
				i++;
			if (input[i] != '\0' && ft_skip_space(input[i]) == 0)
			{
				count++;
				while (input[i] != '\0' && ft_skip_space(input[i]) == 0 && input[i] != '>' && input[i] != '<' && input[i] != '\'' && input[i] != '"')
					i++;
			}
		}
		else if (ft_skip_space(input[i]) == 1 && quote == 0)
		{
			while (ft_skip_space(input[i]) == 1)
				i++;
			if (input[i] != '\0' && input[i] != '>' && input[i] != '<' && ft_skip_space(input[i]) == 0)
				count++;
		}
		else
			i++;
	}
	return count + 1;
}

int check_redirections(char *input)
{
    int	i;
    int	quote;

	i = 0;
	quote = 0;
    while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
        i++;
    if (input[i] == '|')
        return (1);
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            quote = ft_handle_quote(input[i], quote);
            i++;
        }
        else if ((input[i] == '|' || input[i] == '>' || input[i] == '<') && quote == 0)
        {
            if (input[i] == '|')
            {
                i++;
                while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
                    i++;
                if (input[i] == '\0' || input[i] == '|')
                    return (1);
                continue;
            }
            if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
                i += 2;
            else
                i++;
            while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
                i++;
            if (input[i] == '\0' || input[i] == '|' || input[i] == '>' || input[i] == '<')
                return (1);
        }
        else
            i++;
    }
    if (quote != 0)
	{
		if (quote == '\'')
			return (2);
		else
			return (3);
	}
    return (0);
}
