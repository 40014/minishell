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

void    handle_buffer(t_ParserState *state, t_arg_node *arg_list, t_redir_node **redir_list)
{
    state->buffer[state->buf_index] = '\0';
    if (state->find_red == 1)
    {
        append_redir_node(redir_list, create_redir_node(state->buffer));
        state->find_red = 0;
    }
    else
        append_arg_node(arg_list, create_arg_node(state->buffer));
    state->buf_index = 0;
}

void handle_redirection(t_ParserState *state, t_arg_node **arg_list, t_redir_node **redir_list)
{
    int buf_index;
    char buffer[BUFSIZ];
    char    file_quote;

    buf_index = 0;
    if (state->buf_index > 0)
        handle_buffer(state, arg_list, redir_list);
    if (state->input[state->i] == '>' && state->input[state->i + 1] == '>')
    {
        append_redir_node(redir_list, create_redir_node(">>"));
        state->i++;
    }
    else if (state->input[state->i] == '<' && state->input[state->i + 1] == '<')
    {
        append_redir_node(redir_list, create_redir_node("<<"));
        state->i++;
    }
    else if (state->input[state->i] == '>')
        append_redir_node(redir_list, create_redir_node(">"));
    else if (state->input[state->i] == '<')
        append_redir_node(redir_list, create_redir_node("<"));
    state->find_red = 1;
}

int ft_handle_dollar_herdoc(t_ParserState *state, char c)
{
    int i;

    if (state->redir_index > 0 && c == '$')
    {
        if (state->redir_index <= 0)
            return (1);
        i = state->redir_index - 1;
        if (state->redirections[i] != NULL && strcmp(state->redirections[i], "<<") == 0)
            return (0);
    }
    return (1);
}

char **split_line_to_args(char *input, t_env *env_var, t_quots *quots, t_redir_node **redir_list)
{
    int check;
    t_ParserState state;
    t_arg_node *arg_list;

    init_parser_state(&state, input, env_var, quots);
    check = ft_check(input);
    arg_list = NULL;
    *redir_list = NULL;
    while (state.input[state.i] != '\0')
    {
        if (handle_consecutive_quotes(&state) == 1)
        {
            handle_empty_argument(&state, &arg_list);
            continue;
        }
        if ((state.input[state.i] != '\'' && state.input[state.i] != '"') && state.quote == 0 && state.buf_index == 0)
            state.quots->x = 2;
        if ((state.input[state.i] == '\'' || state.input[state.i] == '"') && (state.input[state.i] == state.quote || state.quote == 0) && check == 1)
            handle_quotes(&state);
        else if ((state.input[state.i] == '>' || state.input[state.i] == '<') && state.quote == 0)
            handle_redirection(&state, &arg_list, redir_list); 
        else if (state.input[state.i] == '$' && (state.quote == 0 || state.quote != '\'') && ft_handle_dollar_herdoc(&state, state.input[state.i]) == 1)
            handle_dollar_sign(&state, &arg_list, redir_list);
        else if ((ft_skip_space(state.input[state.i]) == 1) && state.quote == 0)
            add_buffer_to_args(&state, &arg_list, redir_list);
        else
            state.buffer[state.buf_index++] = state.input[state.i];
        state.i++;
    }
    finalize_args(&state, &arg_list, redir_list);
    free(state.buffer);
    state.args = convert_list_to_array(arg_list);
    free_arg_list(arg_list);
    return (state.args);
}
     
int parse_line(t_data **data, char *input, t_env *env_var, t_quots *quots)
{
    char **arguments;
    t_redir_node *redir_list;
    char **redirections;
    char *token;
    char *remaining_input;
    int i;

    i = 0;
    if ((i = check_errors(input)) != 0)
    {
        ft_printf_error(i);
        exit_code = 2;
        return (1);
    }
    if (check_herdoc_error(input) != 0)
    {
        printf("maximum here-document count exceeded\n");
        exit_code = 2;
        return (2);
    }
    ft_check_expansion_herdoc(input, quots);
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        arguments = split_line_to_args(token, env_var, quots, &redir_list);
        if (arguments[0] != NULL || redir_list->redirection[0] != NULL)
            ft_add_node(data, arguments, redir_list);
        else
            return (1);
    }
    return (0);
}
