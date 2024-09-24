#include "../minishell.h"

void handle_empty_argument(t_ParserState *state)
{
    if (state->find_red == 1)
    {
        state->redirections[state->redir_index++] = ft_strdup("");
        state->find_red = 0;
    }
    else
        state->args[state->j++] = ft_strdup("");
    state->i += 2;
}

void add_buffer_to_args(t_ParserState *state)
{
    if (state->buf_index > 0)
    {
        state->buffer[state->buf_index] = '\0';
        if (state->input[state->i] == '>')
            state->find_red = 1;
        if (state->find_red == 1)
        {
            state->redirections[state->redir_index++] = ft_strdup(state->buffer);
            state->buf_index = 0;
            state->find_red = 0;
        }
        else
        {
            state->args[state->j++] = ft_strdup(state->buffer);
            state->buf_index = 0;
        }
    }
}

void finalize_args(t_ParserState *state)
{
    if (state->buf_index > 0)
    {
        state->buffer[state->buf_index] = '\0';
        if (state->find_red == 1)
        {
            state->redirections[state->redir_index++] = ft_strdup(state->buffer);
            state->find_red = 0;
        }
        else
            state->args[state->j++] = ft_strdup(state->buffer);
    }
    if (state->buf_index == 0 && state->j == 0)
    {
        if (state->quots->empty == 1)
            state->quots->empty = 2;
        state->args[0] = ft_strdup("");
        state->j++;
    }
    state->args[state->j] = NULL;
}

void init_parser_state(t_ParserState *state, char *input, t_env *env_var, t_quots *quots)
{
    state->input = input;
    state->buffer = malloc(BUFSIZ);
    state->buf_index = 0;
    state->redir_index = 0;
    state->i = 0;
    state->quote = 0;
    state->env_var = env_var;
    state->quots = quots;
    state->j = 0;
    state->find_red = 0;
    state->quots->empty = 0;
}
