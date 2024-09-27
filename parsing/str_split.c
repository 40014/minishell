#include "../minishell.h"

void free_split_string_on_error(char **result, int idx)
{
    int j;

    j = 0;
    while (j < idx)
    {
        free(result[j]);
        j++;
    }
    free(result);
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

char **split_string(const char *input)
{
    const char *ptr;
    const char *start;
    int count;
    int in_word;
    char **result;
    int len;
    int idx;

    in_word = 0;
    count = 0;
    ptr = input;
    while (*ptr)
    {
        if (!ft_skip_space(*ptr))
        {
            if (!in_word)
            {
                in_word = 1;
                count++;
            }
        }
        else
            in_word = 0;
        ptr++;
    }
    result = malloc((count + 1) * sizeof(char*));
    if (result == NULL)
        return (NULL);
    idx = 0;
    ptr = input;
    while (*ptr)
    {
        while (ft_skip_space(*ptr))
        {
            ptr++;
        }
        if (*ptr)
        {
            start = ptr;
            while (*ptr && !ft_skip_space(*ptr))
                ptr++;
            len = ptr - start;
            result[idx] = malloc((len + 1) * sizeof(char));
            if (result[idx] == NULL)
            {
                free_split_string_on_error(result, idx);
                return (NULL);
            }
            ft_strncpy(result[idx], start, len);
            result[idx][len] = '\0';
            idx++;
        }
    }
    result[idx] = NULL;
    return (result);
}



