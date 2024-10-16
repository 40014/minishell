/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:16:47 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:16:50 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_empty_argument_backslash(t_ParserState *state,
		t_arg_node **arg_list, t_redir_node **redir_list)
{
	if (state->quots->empty == 1 && (*redir_list) == NULL)
		state->quots->empty = 2;
	if ((*arg_list) == NULL && (*redir_list) == NULL)
		append_arg_node(arg_list, create_arg_node(""));
}

int	check_parsing(t_hold_main *main_vars)
{
	main_vars->i = parse_line(&main_vars->data, main_vars->input,
			main_vars->env_var, &main_vars->quots);
	return ((main_vars->i == 0 || main_vars->i == 2)
		&& main_vars->quots.empty != 2);
}

int	is_dollar_followed_by_quote(t_ParserState *state)
{
	return (state->input[state->i] == '$' && (state->input[state->i + 1] == '\"'
			|| state->input[state->i + 1] == '\'') && state->quote == 0);
}
