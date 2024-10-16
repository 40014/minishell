/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:18:57 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:18:59 by momazouz         ###   ########.fr       */
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
	t_ErrorState	state;

	init_error_state(&state);
	if (ft_skip_spaces_and_check_pipe(input, &state.i) == 1)
		return (1);
	while (input[state.i] != '\0')
	{
		if (input[state.i] == '\'' || input[state.i] == '\"')
			ft_handle_quote_and_increment(input, &state.i, &state.quote);
		else if ((input[state.i] == '|' || input[state.i] == '>'
				|| input[state.i] == '<') && state.quote == 0)
		{
			if (input[state.i] == '|')
			{
				if (ft_handle_pipe(input, &state.i) == 1)
					return (1);
				continue ;
			}
			if (ft_handle_redirection(input, &state.i) == 1)
				return (1);
		}
		else
			state.i++;
	}
	return (ft_check_unclosed_quote(state.quote));
}
