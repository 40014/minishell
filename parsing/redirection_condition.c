/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_condition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:14:09 by medo              #+#    #+#             */
/*   Updated: 2024/10/10 00:14:12 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection_condition_1(t_ParserContext *context,
		t_ParserState *state)
{
	append_redir_node(context->redir_list, create_redir_node(NULL));
	state->find_red = 0;
}

void	handle_redirection_condition_2(t_ParserContext *context,
		t_ParserState *state, char *env)
{
	append_redir_node(context->redir_list, create_redir_node(NULL));
	state->find_red = 0;
}

void	handle_redirection_condition_3(t_ParserContext *context,
		t_ParserState *state, char **result)
{
	append_redir_node(context->redir_list, create_redir_node(result[0]));
	state->find_red = 0;
}

void	handle_empty_redirection(t_ParserContext *context, t_ParserState *state)
{
	append_redir_node(context->redir_list, create_redir_node(""));
	state->find_red = 0;
}

void	copy_to_buffer(t_ParserState *state, char *source)
{
	ft_strcpy(state->buffer + state->buf_index, source);
	state->buf_index += ft_strlen(source);
}
