/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:14:57 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:14:59 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_results(char **result)
{
	int	i;

	i = 0;
	if (result == NULL)
		return (i);
	while (result[i] != NULL)
		i++;
	return (i);
}

void	process_buffer_and_append(t_ParserState *state, t_arg_node **arg_list,
		char **result, int *j)
{
	if (state->buf_index > 0)
	{
		if (state->check_first_space == 1)
		{
			state->buffer[state->buf_index] = '\0';
			append_arg_node(arg_list, create_arg_node(state->buffer));
			state->buf_index = 0;
		}
		else
		{
			ft_strcpy(state->buffer + state->buf_index, result[*j]);
			state->buf_index += ft_strlen(result[*j]);
			append_arg_node(arg_list, create_arg_node(state->buffer));
			(*j)++;
			state->buf_index = 0;
		}
	}
}

void	process_remaining_results(t_ParserState *state, t_arg_node **arg_list,
		char **result, int j)
{
	while (result[j + 1] != NULL)
	{
		append_arg_node(arg_list, create_arg_node(result[j]));
		j++;
	}
	ft_strcpy(state->buffer + state->buf_index, result[j]);
	if (state->check_last_space == 1)
	{
		append_arg_node(arg_list, create_arg_node(state->buffer));
		state->buf_index = 0;
	}
	else
	{
		state->buf_index += ft_strlen(result[j]);
	}
}

int	handle_split_env_result(t_ParserState *state, t_arg_node **arg_list,
		char **result, int *check)
{
	int	i;
	int	j;

	i = count_results(result);
	j = 0;
	if (state->input[state->i] == '$' && (state->input[state->i + 1] == '\0'
			|| ft_skip_space(state->input[state->i + 1]) == 1))
		*check = 1;
	if (i > 1 && *check != 1)
	{
		process_buffer_and_append(state, arg_list, result, &j);
		process_remaining_results(state, arg_list, result, j);
	}
	return (i);
}
