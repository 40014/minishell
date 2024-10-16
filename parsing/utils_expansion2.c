/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:19:32 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:19:34 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_buffer_append(t_ParserContext *context, t_ParserState *state,
		char **result)
{
	if (state->buf_index > 0 && state->check_first_space == 1)
	{
		append_arg_node(context->arg_list, create_arg_node(state->buffer));
		state->buf_index = 0;
	}
	ft_strcpy(state->buffer + state->buf_index, result[0]);
	state->buf_index += ft_strlen(result[0]);
	if (state->check_last_space == 1)
	{
		append_arg_node(context->arg_list, create_arg_node(state->buffer));
		state->buf_index = 0;
	}
}

void	process_arg_node(t_ParserContext *context, t_ParserState *state,
		char **result, char *env)
{
	if (state->quote == 0 && state->check_last_space == 1 && context->check != 1
		&& state->buf_index == 0 && (state->input[state->i] == '\0'
			|| ft_skip_space(state->input[state->i]) != 1))
	{
		append_arg_node(context->arg_list, create_arg_node(result[0]));
		state->buf_index = 0;
	}
	else if (state->quote == 0 && context->check != 1)
		handle_buffer_append(context, state, result);
	else
	{
		ft_strcpy(state->buffer + state->buf_index, env);
		state->buf_index += ft_strlen(env);
	}
	free(env);
}

void	process_redirection_without_quotes(t_ParserContext *context,
		t_ParserState *state, char **result, char *env)
{
	if (state->quote == 0 && state->find_red == 1 && context->j > 1)
		handle_redirection_condition_1(context, state);
	else if (state->quote == 0 && state->buf_index > 0
		&& state->check_first_space == 1 && env != NULL)
		handle_redirection_condition_2(context, state);
	else if (state->buf_index > 0 && state->check_first_space == 0
		&& state->quote == 0 && env != NULL)
		handle_redirection_last_space(context, state, result[0]);
	else if (state->quote == 0 && state->check_last_space == 1
		&& state->find_red == 1 && state->input[state->i] != ' ')
		handle_redi_input_condit(context, state, result);
	else if (state->quote == 0 && state->buf_index == 0 && state->find_red == 1
		&& env != NULL)
		handle_redi_buf_or_condit(context, state, result);
	else if (env == NULL && state->find_red == 1
		&& (state->input[state->i] == '\0'
			|| ft_skip_space(state->input[state->i]) == 1)
		&& state->buf_index == 0)
		handle_redirection_condition_1(context, state);
}

void	process_redirection_with_quotes(t_ParserContext *context,
		t_ParserState *state, char *env)
{
	if (state->quote != 0 && state->input[state->i] == '"'
		&& state->find_red == 1 && state->buf_index == 0 && env == NULL)
	{
		if (state->input[state->i + 1] == '\0'
			|| ft_skip_space(state->input[state->i + 1]) == 1)
			handle_empty_redirection(context, state);
	}
	else if (state->quote != 0 && state->find_red == 1 && env != NULL)
		copy_to_buffer(state, env);
}

void	process_redirection(t_ParserContext *context, t_ParserState *state,
		char **result, char *env)
{
	if (state->quote == 0)
	{
		process_redirection_without_quotes(context, state, result, env);
	}
	else
		process_redirection_with_quotes(context, state, env);
	free_env_if_needed(env);
}
