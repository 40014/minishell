/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:38:47 by medo              #+#    #+#             */
/*   Updated: 2024/10/09 15:32:45 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_empty_argument_backslash(t_ParserState *state,
		t_arg_node **arg_list)
{
	if (state->quots->empty == 1)
		state->quots->empty = 2;
	append_arg_node(arg_list, create_arg_node(""));
}
