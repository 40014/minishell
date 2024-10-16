/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:16:30 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:16:32 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotee(char c, char *quote)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int	check_herdoc_error(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quotee(input[i], &quote);
		else if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
		{
			count++;
			i++;
		}
		i++;
	}
	if (count > 16)
		return (1);
	return (0);
}
