#include "../minishell.h"

int ft_check(char *input)
{
    int i;

    i = 0;
    if (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '\'' || input[i] == '\"') && (input[i + 1] == '\'' || input[i + 1] == '\"'))
        {
            if (input[i + 2] == '\0' || input[i + 2] == ' ')
                return (0);
        }
    }
    return (1);
}

void handle_redirection(t_ParserState *state)
{
    if (state->buf_index > 0)
    {
        state->buffer[state->buf_index] = '\0';
        state->args[state->j++] = ft_strdup(state->buffer);
        state->buf_index = 0;
    }
    if (state->input[state->i] == '>')
    {
        if (state->input[state->i + 1] == '>')
        {
            state->args[state->j] = ft_strdup(">>");
            state->i++;
        }
        else
            state->args[state->j] = ft_strdup(">");
    }
    else if (state->input[state->i] == '<')
    {
        if (state->input[state->i + 1] == '<')
        {
            state->args[state->j] = ft_strdup("<<");
            state->i++;
        }
        else
            state->args[state->j] = ft_strdup("<");
    }
    state->j++;
    state->i++;
}

char **split_line_to_args(char *input, t_env *env_var, t_quots *quots)
{
    char **args;
    int check;
    t_ParserState state;

    args = malloc(sizeof(char *) * (ft_count_args(input) + 1));
    if (!args)
        return (NULL);
    init_parser_state(&state, input, env_var, quots);
    state.args = args;
    check = ft_check(input);
    while (state.input[state.i] != '\0')
    {
        if (handle_consecutive_quotes(&state) == 1)
        {
            handle_empty_argument(&state);
            continue;
        }
        if ((state.input[state.i] != '\'' && state.input[state.i] != '"') && state.quote == 0 && state.buf_index == 0)
            state.quots->x = 2;
        if ((state.input[state.i] == '\'' || state.input[state.i] == '"') && (state.input[state.i] == state.quote || state.quote == 0) && check == 1)
            handle_quotes(&state);
        else if ((state.input[state.i] == '>' || state.input[state.i] == '<') && state.quote == 0)
        {
            if (state.buf_index > 0)
            {
                state.buffer[state.buf_index] = '\0';
                state.args[state.j++] = ft_strdup(state.buffer);
                state.buf_index = 0;
            }
            if (state.input[state.i] == '>' && state.input[state.i + 1] == '>')
            {
                state.args[state.j++] = ft_strdup(">>");
                state.i = state.i + 1;
                state.buf_index = 0;
            }
            else if (state.input[state.i] == '<' && state.input[state.i + 1] == '<')
            {
                state.args[state.j++] = ft_strdup("<<");
                state.i = state.i + 1;
                state.buf_index = 0;
            }
            else if (state.input[state.i] == '>')
            {
                state.args[state.j++] = ft_strdup(">");
                state.buf_index = 0;
            }
            else if (state.input[state.i] == '<')
            {
                state.args[state.j++] = ft_strdup("<");
                state.buf_index = 0;
            }
        }
        // else if (state.input[state.i] == '<' || state.input[state.i] == '>' && state.quote == 0)
        //     handle_redirection(&state);
        else if (state.input[state.i] == '$' && (state.quote == 0 || state.quote != '\''))
            handle_dollar_sign(&state);
        else if ((ft_skip_space(state.input[state.i]) == 1) && state.quote == 0)
            add_buffer_to_args(&state);
        else
            state.buffer[state.buf_index++] = state.input[state.i];
        state.i++;
    }
    finalize_args(&state);
    free(state.buffer);
    return (state.args);
}

int parse_line(t_data **data, char *input, t_env *env_var, t_quots *quots)
{
    char **arguments;
    char *token;
    char *remaining_input;
    int i;

    i = 0;
    if ((i = check_redirections(input)) != 0)
    {
        if (i == 2 || i == 3)
        {
            if (i == 2)
                printf("unexpected EOF while looking for matching `\'' \n");
            else
                printf("unexpected EOF while looking for matching `\"' \n");
        }
        else
            printf("minishell: syntax error near unexpected token \n");
        exit_code = 2;
        return (1);
    }
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        arguments = split_line_to_args(token, env_var, quots);
        if (arguments[0] != NULL)
            ft_add_node(data, arguments);
        else
            return (1);
    }
    // i = 0;
    // while (arguments[i])
    // {
    //     printf("arg = %s\n", arguments[i]);
    //     i++;
    // }
    return (0);
}
