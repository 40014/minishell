/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_condition1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:17:08 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:17:10 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_if_needed(char *env)
{
	if (env != NULL)
		free(env);
}

void	handle_redirection_last_space(t_ParserContext *context,
		t_ParserState *state, char *result)
{
	if (state->check_last_space == 1
		&& ft_skip_space(state->input[state->i]) != 1
		&& state->input[state->i] != '\0')
	{
		handle_redirection_condition_1(context, state);
	}
	else
		copy_to_buffer(state, result);
}

void	handle_redi_input_condit(t_ParserContext *context,
		t_ParserState *state, char **result)
{
	if (state->input[state->i] == '\0'
		|| ft_skip_space(state->input[state->i]) == 1)
	{
		handle_redirection_condition_3(context, state, result);
	}
	else
		handle_redirection_condition_1(context, state);
}

void	handle_redi_buf_or_condit(t_ParserContext *context,
		t_ParserState *state, char **result)
{
	if (state->check_last_space != 1 && state->input[state->i] != '\0'
		&& ft_skip_space(state->input[state->i]) != 1)
	{
		copy_to_buffer(state, result[0]);
	}
	else if (ft_skip_space(state->input[state->i]) == 1
		|| (state->input[state->i] == '\0' && state->check_first_space == 0)
		|| state->check_first_space == 1)
		handle_redirection_condition_3(context, state, result);
}
