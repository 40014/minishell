/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:18:26 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:18:28 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_quotes(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		return (1);
	}
	return (0);
}

int	ft_handle_redirection_type(char *input, int i)
{
	if (input[i + 1] == '>' || input[i + 1] == '<')
		return (i + 2);
	else
		return (i + 1);
}

int	ft_process_file_name(char *input, int i, int *count)
{
	char	file_quote;

	file_quote = 0;
	(*count)++;
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
		while (input[i] != '\0' && ft_skip_space(input[i]) == 0
			&& input[i] != '>' && input[i] != '<')
			i++;
	}
	return (i);
}

int	ft_count_redirections(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (input[i] != '\0')
	{
		if (ft_handle_quotes(input[i], &quote) == 1)
			i++;
		else if ((input[i] == '>' || input[i] == '<') && quote == 0)
		{
			count++;
			i = ft_handle_redirection_type(input, i);
			while (input[i] != '\0' && ft_skip_space(input[i]) == 1)
				i++;
			if (input[i] != '\0' && ft_skip_space(input[i]) == 0
				&& input[i] != '>' && input[i] != '<')
				i = ft_process_file_name(input, i, &count);
		}
		else
			i++;
	}
	return (count);
}
