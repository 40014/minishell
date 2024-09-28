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

void process_exit_code(t_ParserState *state)
{
    char *env_val;

    env_val = ft_itoa(exit_code);
    ft_strcpy(state->buffer + state->buf_index, env_val);
    state->buf_index += ft_strlen(env_val);
    free(env_val);
    state->i++;
}

void process_env_variable(t_ParserState *state, t_arg_node **arg_list)
{
    char *env;
    char *env_val;
    char **result;
    int i;
    int j;

    i = 0;
    j = 0;
    if (state->input[state->i + 1] == '?')
        process_exit_code(state);
    else
    {
        state->buffer[state->buf_index] = '\0';
        env_val = replace_env_variable(state->input, &state->i);
        env = ft_environment_variables(env_val, state->env_var, state->quots);
        if (env_val != NULL)
            free(env_val);
        if (state->quote == 0 && env != NULL)
        {
            result = split_string(env);
            while (result[i] != NULL)
                i++;
            if (i > 1)
            {
                if (state->buf_index > 0)
                {

                    ft_strcpy(state->buffer + state->buf_index, result[j]);
                    state->buf_index += ft_strlen(env);
                    append_arg_node(arg_list, create_arg_node(state->buffer));
                    j++;
                    state->buf_index = 0;
                }
                while (result[j] != NULL)
                {
                    append_arg_node(arg_list, create_arg_node(result[j]));
                    j++;
                }
            }
            if (i > 1)
                free(env);
            free_split_string(result);
        }
        if (env != NULL && !(i > 1))
        {
            ft_strcpy(state->buffer + state->buf_index, env);
            state->buf_index += ft_strlen(env);
            free(env);
        }
        else if (env == NULL && state->quots->x == 0 && state->buf_index == 0 && state->input[state->i] == '\"' && state->input[state->i + 1] == ' ' && state->quote != 0)
            append_arg_node(arg_list, create_arg_node(""));
        if (env == NULL && state->find_red == 1)
            state->find_red = 0;
        while (state->input[state->i] != '\0' && state->input[state->i] != ' ' && state->input[state->i] != '\'' && state->input[state->i] != '"' && state->input[state->i] != '$')
            state->buffer[state->buf_index++] = state->input[state->i++];
        state->i--;
    }
}

void handle_dollar_sign(t_ParserState *state, t_arg_node **arg_list)
{
    int temp_i;
    int check_dollar;

    check_dollar = 0;
    if (state->input[state->i] == '$' && (state->quote == 0 || state->quote != '\''))
    {
        if (state->quote == 0)
            state->quots->empty = 1;
        if (state->input[state->i] == '$' && (state->input[state->i + 1] == '\"' || state->input[state->i + 1] == '\'') && state->quote == 0)
        {
            state->i++;
            check_dollar = 1;
        }
        temp_i = state->i + 1;
        while (state->input[temp_i] == ' ' || state->input[temp_i] == '\"' || state->input[temp_i] == '\'')
            temp_i++;
        if (state->input[temp_i] == '\0' && check_dollar != 1)
            state->buffer[state->buf_index++] = '$';
        else
            process_env_variable(state, arg_list);
    }
}

void handle_quotes(t_ParserState *state)
{
    if (state->input[state->i] == '\'' || state->input[state->i] == '"')
    {
        if (state->input[state->i] == '\"')
            state->quots->x = 0;
        else
            state->quots->x = 1;
        if (state->quote == 0)
            state->quote = state->input[state->i];
        else if (state->quote == state->input[state->i])
            state->quote = 0;
    }
}

int handle_consecutive_quotes(t_ParserState *state)
{
    if ((state->input[state->i] == '\"' && state->input[state->i + 1] == '\"') &&
        (state->input[state->i + 2] != '\"' || state->input[state->i + 2] == '\0') &&
        (state->input[state->i + 2] == ' ' || state->input[state->i + 2] == '\0') &&
        state->quote == 0 && state->buf_index == 0)
    {
        return (1);
    }
    if ((state->input[state->i] == '\'' && state->input[state->i + 1] == '\'') &&
        (state->input[state->i + 2] != '\'' || state->input[state->i + 2] == '\0') &&
        (state->input[state->i + 2] == ' ' || state->input[state->i + 2] == '\0') &&
        state->quote == 0 && state->buf_index == 0)
    {
        return (1);
    }
    return (0);
}
