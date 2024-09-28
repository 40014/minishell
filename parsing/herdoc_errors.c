#include "../minishell.h"

int check_herdoc_error(char *input)
{
    int i;
    int count;
    int quote;

    i = 0;
    count = 0;
    quote = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
        {
            count++;
            i++;
        }
        i++;

    }
    if (count > 16)
        return (1);
    return (0);
}
