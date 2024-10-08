/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:52:09 by medo              #+#    #+#             */
/*   Updated: 2024/10/09 23:53:14 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_unclosed_quote(int quote)
{
	if (quote != 0)
	{
		if (quote == '\'')
			return (2);
		else
			return (3);
	}
	return (0);
}

void	ft_handle_quote_and_increment(char *input, int *i, int *quote)
{
	*quote = ft_handle_quote(input[*i], *quote);
	(*i)++;
}

int	handle_quots(char *input, int *i, int *quote)
{
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		ft_handle_quote_and_increment(input, i, quote);
		return (1);
	}
	return (0);
}

int	handle_redirection_errors(char *input, int *i, int quote)
{
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
	{
		if (quote == 0)
		{
			if (input[*i] == '|')
			{
				if (ft_handle_pipe(input, i) == 1)
					return (1);
				return (0);
			}
			if (ft_handle_redirection(input, i) == 1)
				return (1);
		}
	}
	return (0);
}

int	check_errors(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (ft_skip_spaces_and_check_pipe(input, &i) == 1)
		return (1);
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
			ft_handle_quote_and_increment(input, &i, &quote);
		else if ((input[i] == '|' || input[i] == '>' || input[i] == '<')
			&& quote == 0)
		{
			if (input[i] == '|')
			{
				if (ft_handle_pipe(input, &i) == 1)
					return (1);
				continue ;
			}
			if (ft_handle_redirection(input, &i) == 1)
				return (1);
		}
		else
			i++;
	}
	return (ft_check_unclosed_quote(quote));
}

// int	check_errors(char *input)
// {
// 	int	i;
// 	int	quote;

// 	i = 0;
// 	quote = 0;
// 	if (ft_skip_spaces_and_check_pipe(input, &i) == 1)
// 		return (1);
// 	while (input[i] != '\0')
// 	{
// 		if (handle_quots(input, &i, &quote))
// 			continue ;
// 		if (handle_redirection_errors(input, &i, quote) == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (ft_check_unclosed_quote(quote));
// }
