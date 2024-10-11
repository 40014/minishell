/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:49:47 by medo              #+#    #+#             */
/*   Updated: 2024/10/11 00:56:54 by momazouz         ###   ########.fr       */
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
		exit_code = 2;
		return (1);
	}
	if (check_herdoc_error(input) != 0)
	{
		printf("maximum here-document count exceeded\n");
		exit_code = 2;
		return (2);
	}
	return (0);
}

int	ft_handle_dollar_herdoc(char c, t_redir_node **redir_list)
{
	t_redir_node	*current;

	if (c == '$' && redir_list != NULL && *redir_list != NULL)
	{
		current = *redir_list;
		while (current->next != NULL)
			current = current->next;
		if (current->redirection != NULL && ft_strcmp(current->redirection,
				"<<") == 0)
			return (0);
	}
	return (1);
}
