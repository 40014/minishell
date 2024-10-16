/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:19:06 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:19:08 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_error_state(t_ErrorState *state)
{
	state->i = 0;
	state->quote = 0;
}

int	ft_handle_pipe(char *input, int *i)
{
	(*i)++;
	while (input[*i] != '\0' && ft_skip_space(input[*i]) == 1)
		(*i)++;
	if (input[*i] == '\0' || input[*i] == '|')
		return (1);
	return (0);
}

int	ft_handle_redirection(char *input, int *i)
{
	if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<'
			&& input[*i + 1] == '<'))
		(*i) += 2;
	else
		(*i)++;
	while (input[*i] != '\0' && ft_skip_space(input[*i]) == 1)
		(*i)++;
	if (input[*i] == '\0' || input[*i] == '|' || input[*i] == '>'
		|| input[*i] == '<')
		return (1);
	return (0);
}
