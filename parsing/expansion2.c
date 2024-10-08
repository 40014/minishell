/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:30:19 by medo              #+#    #+#             */
/*   Updated: 2024/10/08 20:30:20 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void free_split_string(char **words)
{
    int i;

    i = 0;
    if (words == NULL)
        return;
    while (words[i] != NULL)
    {
        free(words[i]);
        i++;
    }
    free(words);
}

char *handle_env_variable(t_ParserState *state)
{
    char *env_val;
    char *env;

    state->buffer[state->buf_index] = '\0';
    env_val = replace_env_variable(state->input, &state->i);
    env = ft_environment_variables(env_val, state->env_var, state->quots);
    if (env_val != NULL)
        free(env_val);
    return (env);
}

void free_env_result(char **env, char **result, int i, int check)
{
    if (i > 1 && check != 1)
    {
        free(*env);
        *env = NULL;
    }
    free_split_string(result);
}

void handle_null_env_or_redir(t_ParserContext *context, char *env, int check, int i)
{
    t_ParserState *state;
    int j;
    char **result;

    state = context->state;
    result = split_string(env, state);
    j = count_results(result);
    if (env != NULL && state->find_red != 1 && (!(i > 1) || check == 1))
    {
        if (state->quote == 0 && state->check_last_space == 1 && check != 1 && state->buf_index == 0 && (state->input[state->i] == '\0' || ft_skip_space(state->input[state->i]) != 1))
        {
            append_arg_node(context->arg_list, create_arg_node(result[0]));
            state->buf_index = 0;
        }
        else if (state->quote == 0 && check != 1)
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
        else
        {
            ft_strcpy(state->buffer + state->buf_index, env);
            state->buf_index += ft_strlen(env);
        }
        free(env);
    }
    else if (env == NULL && state->quots->x == 0 && state->buf_index == 0 && state->input[state->i] == '\"' && ft_skip_space(state->input[state->i + 1]) == 1 && state->quote != 0 && state->find_red != 1)
        append_arg_node(context->arg_list, create_arg_node(""));
    if (env == NULL || state->find_red == 1)
    {
        if (state->quote == 0 && state->find_red == 1 && j > 1)
        {
            append_redir_node(context->redir_list, create_redir_node(NULL));
            state->find_red = 0;
        }
        else if (state->quote == 0 && state->buf_index > 0 && state->check_first_space == 1 && env != NULL)
        {
            append_redir_node(context->redir_list, create_redir_node(NULL));
            state->find_red = 0;
        }
        else if (state->buf_index > 0 && state->check_first_space == 0 && state->quote == 0 && env != NULL)
        {
            if (state->check_last_space == 1 && ft_skip_space(state->input[state->i]) != 1 && state->input[state->i] != '\0')
            {
                append_redir_node(context->redir_list, create_redir_node(NULL));
                state->find_red = 0;
            }
            else
            {
                ft_strcpy(state->buffer + state->buf_index, result[0]);
                state->buf_index += ft_strlen(result[0]);
            }
        }
        else if (state->quote != 0 && state->input[state->i] == '"' && state->find_red == 1 && state->buf_index == 0 && env == NULL)
        {
            if (state->input[state->i + 1] == '\0' || ft_skip_space(state->input[state->i + 1]) == 1)
            {
                append_redir_node(context->redir_list, create_redir_node(""));
                state->find_red = 0;
            }
        }
        else if (state->quote != 0 && state->find_red == 1 && env != NULL)
        {
            ft_strcpy(state->buffer + state->buf_index, env);
            state->buf_index += ft_strlen(env);
        }
        else if (state->quote == 0 && state->check_last_space == 1 && state->find_red == 1 && state->input[state->i] != ' ')
        {
            if (state->input[state->i] == '\0' || ft_skip_space(state->input[state->i]) == 1)
                append_redir_node(context->redir_list, create_redir_node(result[0]));
            else
                append_redir_node(context->redir_list, create_redir_node(NULL));
            state->find_red = 0;
        }
        else if (state->quote == 0 && state->buf_index == 0 && state->find_red == 1 && env != NULL)
        {
            if (state->check_last_space != 1 && state->input[state->i] != '\0' && ft_skip_space(state->input[state->i]) != 1)
            {
                ft_strcpy(state->buffer + state->buf_index, result[0]);
                state->buf_index += ft_strlen(result[0]);
            }
            else if (ft_skip_space(state->input[state->i]) == 1 || state->input[state->i] == '\0' && state->check_first_space == 0 || state->check_first_space == 1)
            {
                append_redir_node(context->redir_list, create_redir_node(result[0]));
                state->find_red = 0;
            }
        }
        else if (env == NULL && state->find_red == 1 && (state->input[state->i] == '\0' || ft_skip_space(state->input[state->i]) == 1))
        {
            append_redir_node(context->redir_list, create_redir_node(NULL));
            state->find_red = 0;
        }
        if (env != NULL)
            free(env);
    }
    free_split_string(result);
}

// int handle_split_env_result(t_ParserState *state, t_arg_node **arg_list, char **result, int *check)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while (result[i] != NULL)
//         i++;
//     if (state->input[state->i] == '$' && (state->input[state->i + 1] == '\0' || ft_skip_space(state->input[state->i + 1]) == 1))
//         *check = 1;
//     if (i > 1 && *check != 1)
//     {
//         if (state->buf_index > 0)
//         {
//             if (state->check_first_space == 1)
//             {
//                 state->buffer[state->buf_index] = '\0';
//                 append_arg_node(arg_list, create_arg_node(state->buffer));
//                 state->buf_index = 0;
//             }
//             else
//             {
//                 ft_strcpy(state->buffer + state->buf_index, result[j]);
//                 state->buf_index += ft_strlen(result[j]);
//                 append_arg_node(arg_list, create_arg_node(state->buffer));
//                 j++;
//                 state->buf_index = 0;
//             }
//         }
//         while (result[j + 1] != NULL)
//         {
//             append_arg_node(arg_list, create_arg_node(result[j]));
//             j++;
//         }
//         ft_strcpy(state->buffer + state->buf_index, result[j]);
//         if (state->check_last_space == 1)
//         {
//             append_arg_node(arg_list, create_arg_node(state->buffer));
//             state->buf_index = 0;
//         }
//         else
//             state->buf_index += ft_strlen(result[j]);
//     }
//     return (i);
// }
