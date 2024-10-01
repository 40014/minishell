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

void process_env_variable(t_ParserState *state, t_arg_node **arg_list, t_redir_node **redir_list)
{
    char *env;
    char *env_val;
    char **result;
    int i;
    int j;
    int check;

    i = 0;
    j = 0;
    check = 0;
    if (state->input[state->i + 1] == '?')
        process_exit_code(state);
    else
    {
        state->buffer[state->buf_index] = '\0';
        env_val = replace_env_variable(state->input, &state->i);
        env = ft_environment_variables(env_val, state->env_var, state->quots);
        if (env_val != NULL)
            free(env_val);
        //printf("state i = %c\n", state->input[state->i]);
        // && state->input[state->i] != '$'
        if (state->quote == 0 && env != NULL && state->find_red != 1)
        {
            result = split_string(env, state);
            while (result[i] != NULL)
                i++;
            //printf("last argument = '%s', state = %d\n", result[i - 1], state->check_last_space);
            if (state->input[state->i] == '$' && (state->input[state->i + 1] == '\0' || (ft_skip_space(state->input[state->i + 1]) == 1)) )
                check = 1;
            //printf("check = %d\n", check);
            if (i > 1 && check != 1)
            {
                // printf("buf indix = %d\n", state->buf_index);
                // if (state->input[state->i] != '$')
                //     check = 1;
                if (state->buf_index > 0)
                {
                    ft_strcpy(state->buffer + state->buf_index, result[j]);
                    state->buf_index += ft_strlen(env);
                    append_arg_node(arg_list, create_arg_node(state->buffer));
                    j++;
                    state->buf_index = 0;
                }
                while (result[j + 1] != NULL)
                {
                    //printf("add to argument\n");
                    append_arg_node(arg_list, create_arg_node(result[j]));
                    j++;
                }
                ft_strcpy(state->buffer + state->buf_index, result[j]);
                //printf("buffer = %s\n", state->buffer);
                if (state->check_last_space == 1)
                {
                    append_arg_node(arg_list, create_arg_node(state->buffer));
                    state->buf_index = 0;
                }
                else
                    state->buf_index += ft_strlen(result[j]);
            }
            if (i > 1 && check != 1)
                free(env);
            free_split_string(result);
        }
        if (env != NULL && !(i > 1) || check == 1)
        {
            ft_strcpy(state->buffer + state->buf_index, env);
            state->buf_index += ft_strlen(env);
            free(env);
        }
        else if (env == NULL && state->quots->x == 0 && state->buf_index == 0 && state->input[state->i] == '\"' && state->input[state->i + 1] == ' ' && state->quote != 0)
            append_arg_node(arg_list, create_arg_node(""));
        if (env == NULL && state->find_red == 1)
        {
            append_redir_node(redir_list, create_redir_node(NULL));
            state->find_red = 0;
        }
        while (state->input[state->i] != '\0' && ft_skip_space(state->input[state->i]) != 1 && state->input[state->i] != '\'' && state->input[state->i] != '"' && state->input[state->i] != '$')
            state->buffer[state->buf_index++] = state->input[state->i++];
        state->i--;
    }
}

void handle_dollar_sign(t_ParserState *state, t_arg_node **arg_list, t_redir_node **redir_list)
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
            process_env_variable(state, arg_list, redir_list);
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
