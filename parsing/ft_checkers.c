#include "../minishell.h"

int ft_skip_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int ft_count_args(char *input)
{
	int count;
	int i;
	char quote;

	count = 0;
	i = 0;
	quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = ft_handle_quote(input[i], quote);
			i++;
		}
		else if (ft_skip_space(input[i]) == 1 && quote == 0)
		{
			while (ft_skip_space(input[i]) == 1)
				i++;
			if (input[i] == '\0')
				break;
			count++;
		}
		else
			i++;
	}
	return (count + 1);
}

int check_qout(char *input)
{
	int i;
	int flag;
	int quote;
	int count;

	i = 0;
	flag = 0;
	quote = 0;
	count = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == 0)
			{
				quote = input[i];
				flag = 1;
			}
			else if (quote == input[i])
			{
				quote = 0;
				flag = 0;
			}
		}
		else if (input[i] == '|' && quote == 0)
		{
			if (input[i] == '|' && input[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (flag);
}

int check_redirections(char *input)
{
	int i;
	int quote;
	int	j;

	i = 0;
	j = 0;
	quote = 0;
	while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
		i++;
	if (input[i] == '|')
		return (1);
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
				quote = ft_handle_quote(input[i], quote);
		else if ((input[i] == '|' || (input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' || input[i] == '<')) && quote == 0)
		{
			if (input[i] == '|')
			{
				i++;
				j = 1;
				while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
					i++;
				if (input[i] == '\0')
					return (1);
			}
			if (input[i] == '>' && input[i + 1] == '>' || input[i] == '<' && input[i + 1] == '<')
				i = i + 2;
			else if (j != 1)
				i++;
			while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
				i++;
			if ((input[i] == '\0' || input[i] == '|' || (input[i] == '>' || input[i] == '<')) && j != 1 && quote == 0)
				return (1);
			j = 0;
		}
		i++;
	}
	return (0);
}
