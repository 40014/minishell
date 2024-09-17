#include "../minishell.h"

void process_env_variable(t_ParserState *state)
{
    char *env;
    char *env_val;

    if (state->input[state->i + 1] == '?')
    {
        env_val = ft_itoa(exit_code);
        ft_strcpy(state->buffer + state->buf_index, env_val);
        state->buf_index += ft_strlen(env_val);
        free(env_val);
        state->i++;
    }
    else
    {
        state->buffer[state->buf_index] = '\0';
        env_val = replace_env_variable(state->input, &state->i);
        env = ft_environment_variables(env_val, state->env_var, state->quots);
        if (env_val != NULL)
            free(env_val);
        if (env != NULL)
        {
            ft_strcpy(state->buffer + state->buf_index, env);
            state->buf_index += ft_strlen(env);
            free(env);
        }
        else if (env == NULL && state->quots->x == 0 && state->buf_index == 0 && state->input[state->i] == '\"' && state->input[state->i + 1] == ' ' && state->quote != 0)
            state->args[state->j++] = ft_strdup("");
        while (state->input[state->i] != '\0' && state->input[state->i] != ' ' && state->input[state->i] != '\'' && state->input[state->i] != '"' && state->input[state->i] != '$')
            state->buffer[state->buf_index++] = state->input[state->i++];
        state->i--;
    }
}

void handle_dollar_sign(t_ParserState *state)
{
    int temp_i;

    if (state->input[state->i] == '$' && (state->quote == 0 || state->quote != '\''))
    {
        if (state->quote == 0)
            state->quots->empty = 1;
        if (state->input[state->i] == '$' && (state->input[state->i + 1] == '\"' || state->input[state->i + 1] == '\'') && state->quote == 0)
            state->i++;
        temp_i = state->i + 1;
        while (state->input[temp_i] == ' ' || state->input[temp_i] == '\"' || state->input[temp_i] == '\'')
            temp_i++;

        if (state->input[temp_i] == '\0' || state->input[temp_i] == ' ' || state->input[temp_i] == '\"' || state->input[temp_i] == '\'')
            state->buffer[state->buf_index++] = '$';
        else
            process_env_variable(state);
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
