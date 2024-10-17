/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:15:16 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/16 18:06:03 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skip_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	check_prompt(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (3);
	while (input[i] != '\0')
	{
		while ((input[i] == '\t' || input[i] == '\n' || input[i] == '\v'
				|| input[i] == '\f' || input[i] == '\r' || input[i] == ' ')
			&& (input[i] != '\0'))
			i++;
		if (input[i] == '\0')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	ft_check(char *input)
{
	int	i;

	i = 0;
	if (input[i])
	{
		while (ft_skip_space(input[i]) == 1)
			i++;
		if ((input[i] == '\'' || input[i] == '\"') && (input[i + 1] == '\''
				|| input[i + 1] == '\"'))
		{
			if (input[i + 2] == '\0' || ft_skip_space(input[i + 2]) == 1)
				return (0);
		}
	}
	return (1);
}

int	handle_errors(char *input)
{
	int	i;

	i = check_errors(input);
	if (i != 0)
	{
		ft_printf_error(i);
		g_exit_code = 2;
		return (1);
	}
	if (check_herdoc_error(input) != 0)
	{
		ft_putstr_fd("maximum here-document count exceeded\n");
		g_exit_code = 2;
		return (2);
	}
	return (0);
}

int	ft_handle_dollar_herdoc(t_ParserState *state, t_redir_node **redir_list)
{
	t_redir_node	*current;

	if (state->input[state->i] == '$' && redir_list != NULL
		&& *redir_list != NULL)
	{
		current = *redir_list;
		while (current->next != NULL)
			current = current->next;
		if (current->redirection != NULL && ft_strcmp(current->redirection,
				"<<") == 0)
		{
			if (state->input[state->i] == '$' && state->quote == 0
				&& is_quote_next(state->input[state->i + 1]) == 1)
			{
				state->i++;
				state->find_dollar_herd = 1;
			}
			return (0);
		}
	}
	return (1);
}
