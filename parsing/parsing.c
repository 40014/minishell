/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:16:56 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:16:58 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_buffer(t_ParserState *state, t_arg_node **arg_list,
		t_redir_node **redir_list)
{
	state->buffer[state->buf_index] = '\0';
	if (state->find_red == 1)
	{
		append_redir_node(redir_list, create_redir_node(state->buffer));
		state->find_red = 0;
	}
	else
		append_arg_node(arg_list, create_arg_node(state->buffer));
	state->buf_index = 0;
}

void	handle_redirection(t_ParserState *state, t_arg_node **arg_list,
		t_redir_node **redir_list)
{
	if (state->buf_index > 0)
		handle_buffer(state, arg_list, redir_list);
	if (state->input[state->i] == '>' && state->input[state->i + 1] == '>')
	{
		append_redir_node(redir_list, create_redir_node(">>"));
		state->i++;
	}
	else if (state->input[state->i] == '<' && state->input[state->i + 1] == '<')
	{
		append_redir_node(redir_list, create_redir_node("<<"));
		state->i++;
	}
	else if (state->input[state->i] == '>')
		append_redir_node(redir_list, create_redir_node(">"));
	else if (state->input[state->i] == '<')
		append_redir_node(redir_list, create_redir_node("<"));
	state->find_red = 1;
}

void	handle_input_cases(t_ParserState *state, t_arg_node **arg_list,
		t_redir_node **redir_list, int check)
{
	if ((state->input[state->i] != '\'' && state->input[state->i] != '"')
		&& state->quote == 0 && state->buf_index == 0)
		state->quots->x = 2;
	if ((state->input[state->i] == '\'' || state->input[state->i] == '"')
		&& (state->input[state->i] == state->quote || state->quote == 0)
		&& check == 1)
	{
		handle_quotes(state);
	}
	else if ((state->input[state->i] == '>' || state->input[state->i] == '<')
		&& state->quote == 0)
		handle_redirection(state, arg_list, redir_list);
	else if (state->input[state->i] == '$' && (state->quote == 0
			|| state->quote != '\'')
		&& ft_handle_dollar_herdoc(state, redir_list) == 1)
	{
		handle_dollar_sign(state, arg_list, redir_list);
	}
	else if (ft_skip_space(state->input[state->i]) == 1 && state->quote == 0)
		add_buffer_to_args(state, arg_list, redir_list);
	else if (state->find_dollar_herd == 0)
		state->buffer[state->buf_index++] = state->input[state->i];
}

char	**split_line_to_args(char *input, t_env *env_var, t_quots *quots,
		t_redir_node **redir_list)
{
	int				check;
	t_ParserState	state;
	t_arg_node		*arg_list;

	init_parser_state(&state, input, env_var, quots);
	check = ft_check(input);
	arg_list = NULL;
	*redir_list = NULL;
	while (state.input[state.i] != '\0')
	{
		if (handle_consecutive_quotes(&state) == 1)
		{
			handle_empty_argument(&state, &arg_list, redir_list);
			continue ;
		}
		handle_input_cases(&state, &arg_list, redir_list, check);
		if (state.find_dollar_herd == 0)
			state.i++;
		state.find_dollar_herd = 0;
	}
	finalize_args(&state, &arg_list, redir_list);
	free(state.buffer);
	state.args = convert_list_to_array(arg_list);
	free_arg_list(arg_list);
	return (state.args);
}

int	parse_line(t_data **data, char *input, t_env *env_var, t_quots *quots)
{
	char			**arguments;
	t_redir_node	*redir_list;
	char			*token;
	char			*remaining_input;
	int				error_result;

	redir_list = NULL;
	error_result = handle_errors(input);
	if (error_result != 0)
		return (error_result);
	ft_check_expansion_herdoc(input, quots);
	remaining_input = input;
	token = strsplit_by_pipe(&remaining_input);
	while (token != NULL)
	{
		arguments = split_line_to_args(token, env_var, quots, &redir_list);
		if (arguments[0] != NULL || (redir_list != NULL
				&& redir_list->redirection != NULL))
			ft_add_node(data, arguments, redir_list);
		else
			return (1);
		token = strsplit_by_pipe(&remaining_input);
	}
	return (0);
}
