/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:14:49 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:14:51 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split_string(char **words)
{
	int	i;

	i = 0;
	if (words == NULL)
		return ;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	*handle_env_variable(t_ParserState *state)
{
	char	*env_val;
	char	*env;

	state->buffer[state->buf_index] = '\0';
	env_val = replace_env_variable(state->input, &state->i);
	env = ft_environment_variables(env_val, state->env_var, state->quots);
	if (env_val != NULL)
		free(env_val);
	return (env);
}

void	free_env_result(char **env, char **result, int i, int check)
{
	if (i > 1 && check != 1)
	{
		free(*env);
		*env = NULL;
	}
	free_split_string(result);
}

void	handle_null_env_or_redir(t_ParserContext *context, char *env, int check,
		int i)
{
	t_ParserState	*state;
	char			**result;

	state = context->state;
	result = split_string(env, state);
	context->j = count_results(result);
	context->check = check;
	if (env != NULL && state->find_red != 1 && (!(i > 1) || check == 1))
	{
		process_arg_node(context, state, result, env);
	}
	else if (env == NULL && state->quots->x == 0 && state->buf_index == 0
		&& state->input[state->i] == '\"' && state->quote != 0
		&& ft_skip_space(state->input[state->i + 1]) == 1
		&& state->find_red != 1)
		append_arg_node(context->arg_list, create_arg_node(""));
	if (env == NULL || state->find_red == 1)
	{
		process_redirection(context, state, result, env);
	}
	free_split_string(result);
}
