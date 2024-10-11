/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:38:47 by medo              #+#    #+#             */
/*   Updated: 2024/10/11 00:53:15 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_empty_argument_backslash(t_ParserState *state,
		t_arg_node **arg_list, t_redir_node **redir_list)
{
	if (state->quots->empty == 1)
		state->quots->empty = 2;
	if ((*arg_list) == NULL && (*redir_list) == NULL)
		append_arg_node(arg_list, create_arg_node(""));
}
