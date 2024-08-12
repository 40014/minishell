#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>



char    **split_line_to_args(char *input)
{
    char    **args;
    int i;
    int j;
    char    quote;
    char    buffer[1024];
    int buf_index;
    int flag = 0;

    i = 0;
    j = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * ft_count_args(input) + 1);
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == ' ' && quote == 0)
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                args[j++] = ft_strdup(buffer);
                buf_index = 0;
            }
            while (input[i] == ' ')
                i++;
            if (input[i] == '\0')
                break;
            if (flag == 1)
                buffer[buf_index++] = ' ';
            flag = 1;
            i--;
        }
        else
            buffer[buf_index++] = input[i];
        i++;
    }
    if (buf_index > 0)
    {
        buffer[buf_index] = '\0';
        args[j++] = ft_strdup(buffer);
    }
    args[j] = NULL;
    return (args);
}

void  parse_line(t_data **data, char *input)
{
    char    *command;
    char    **arguments;
    char    *token;
    char    *remaining_input;
    int i;

    i = 0;
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        printf("%s\n", token);
        arguments = split_line_to_args(token);
        if (arguments[0] != NULL)
        {
            command = arguments[0];
            while (arguments[i] != NULL)
            {
                arguments[i] = arguments[i + 1];
                i++;
            }
            ft_add_node(data, command, arguments);
            i = 0;
        }
    }
    // i = 0;
    // while (arguments[i] != NULL)
    // {
    //     printf("%s", arguments[i]);
    //     i++;
    // }
}

// void    print_use_list(t_data *head)
// {
//     t_data  *temp;
//     int i = 0;

//     temp = head;
//     //printf("command: %s\n", temp->command);
//     while (temp->argumment[i] != NULL)
//     {
//         printf("%s", temp->argumment[i]);
//         i++;
//     }
// }

void print_commands(t_data *head)
{
    t_data *temp = head;
    while (temp)
    {
        printf("Command:%s\n", temp->command);
        for (int i = 0; temp->argumment[i] != NULL; i++) {
            printf("Arg %d:%s\n", i, temp->argumment[i]);
        }
        temp = temp->next;
        if (temp) {
            printf("---- Next Command ----\n");
        }
    }
}

void ft_free_list(t_data *head)
{
    t_data *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->command);
        if (temp->argumment)
        {
            for (int i = 0; temp->argumment[i] != NULL; i++)
            {
                free(temp->argumment[i]);
            }
            free(temp->argumment);
        }
        free(temp);
    }
}

int main()
{
    t_data  *data;
    char    *input;
    char    *str;
    int i = 0;

    data = NULL;
    while (1)
    {
        input = readline("minishell $> ");
        if (input[0] != '\0')
        {
            parse_line(&data, input);
        }
        // print_commands(data);
        ft_free_list(data); //comming
        data = NULL;
        free(input);
        //data = NULL;
    }
}
