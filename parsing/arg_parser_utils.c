/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:13:46 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/16 17:58:25 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_next_char_not_dquote_or_null(t_ParserState *state, int index)
{
	return (state->input[index] != '\"' || state->input[index] == '\0');
}

int	is_next_char_not_squote_or_null(t_ParserState *state, int index)
{
	return (state->input[index] != '\'' || state->input[index] == '\0');
}

int	is_next_char_space_or_null(t_ParserState *state, int index)
{
	return (ft_skip_space(state->input[index]) == 1
		|| state->input[index] == '\0');
}

int	is_special_char(char c)
{
	return (ft_skip_space(c) == 1 || c == '\"' || c == '\'');
}

void	process_buffer_until_special_char(t_ParserState *state)
{
	while (state->input[state->i] != '\0'
		&& ft_skip_space(state->input[state->i]) != 1
		&& state->input[state->i] != '>' && state->input[state->i] != '<'
		&& state->input[state->i] != '\'' && state->input[state->i] != '"'
		&& state->input[state->i] != '$' && state->buf_index < BUFSIZ - 1)
	{
		state->buffer[state->buf_index++] = state->input[state->i++];
	}
}
