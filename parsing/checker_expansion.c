/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:14:15 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:14:19 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote_next(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

void	ft_process_quote(char *input, int *i, char *quote)
{
	*quote = ft_handle_quote(input[*i], *quote);
	(*i)++;
}

void	ft_check_expansion_herdoc(char *input, t_quots *quots)
{
	int		i;
	char	quote;

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
				break ;
		}
		else
			i++;
	}
}
