/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:51:59 by medo              #+#    #+#             */
/*   Updated: 2024/10/08 20:33:18 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_first_space(const char *input, t_ParserState *state)
{
	if (ft_skip_space(input[0]) == 1)
		state->check_first_space = 1;
	else
		state->check_first_space = 0;
}

void	check_last_space(const char *input, t_ParserState *state, int len)
{
	if (ft_skip_space(input[len - 1]) == 1)
		state->check_last_space = 1;
	else
		state->check_last_space = 0;
}

int	count_words(const char *input)
{
	const char	*ptr;
	int			in_word;
	int			count;

	ptr = input;
	in_word = 0;
	count = 0;
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
	return (count);
}

int	fill_result_array(const char *input, char **result, t_ParserState *state)
{
	const char	*ptr;
	const char	*start;
	int			idx;
	int			len;

	ptr = input;
	idx = 0;
	while (*ptr)
	{
		while (ft_skip_space(*ptr))
			ptr++;
		if (*ptr)
		{
			start = ptr;
			while (*ptr && !ft_skip_space(*ptr))
				ptr++;
			len = ptr - start;
			if (allocate_and_store_word(result, idx, start, len) == -1)
				return (handle_allocation_error(result, idx));
			idx++;
		}
	}
	result[idx] = NULL;
	return (idx);
}

char	**split_string(const char *input, t_ParserState *state)
{
	int		count;
	char	**result;

	if (input == NULL)
		return (NULL);
	check_first_space(input, state);
	count = count_words(input);
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (fill_result_array(input, result, state) == -1)
		return (NULL);
	check_last_space(input, state, ft_strlen(input));
	return (result);
}
// idx = 0;
// ptr = input;
// while (*ptr)
// {
//     while (ft_skip_space(*ptr))
//         ptr++;
//     if (*ptr)
//     {
//         start = ptr;
//         while (*ptr && !ft_skip_space(*ptr))
//             ptr++;
//         len = ptr - start;
//         result[idx] = malloc((len + 1) * sizeof(char));
//         if (result[idx] == NULL)
//         {
//             free_split_string_on_error(result, idx);
//             return (NULL);
//         }
//         ft_strncpy(result[idx], start, len);
//         if (*ptr && ft_skip_space(*ptr))
//         {
//             while (ft_skip_space(*ptr))
//                 ptr++;
//             if (*ptr == '\0')
//             {
//                 state->check_last_space = 1;
//                 result[idx][len] = '\0';
//             }
//             else
//             {
//                 state->check_last_space = 0;
//                 result[idx][len] = '\0';
//             }
//         }
//         else
//             result[idx][len] = '\0';
//         idx++;
//     }
// }
// result[idx] = NULL;
// return (result);
//}

// char **split_string(const char *input, t_ParserState *state)
// {
//     const char *ptr;
//     const char *start;
//     int count;
//     int in_word;
//     char **result;
//     int len;
//     int idx;

//     in_word = 0;
//     count = 0;
//     ptr = input;
//     if (input == NULL)
//         return (NULL);
//     if (input[0] == ' ')
//         state->check_first_space = 1;
//     else
//         state->check_first_space = 0;
//     while (*ptr)
//     {
//         if (!ft_skip_space(*ptr))
//         {
//             if (!in_word)
//             {
//                 in_word = 1;
//                 count++;
//             }
//         }
//         else
//             in_word = 0;
//         ptr++;
//     }
//     result = malloc((count + 1) * sizeof(char*));
//     if (result == NULL)
//         return (NULL);
//     idx = 0;
//     ptr = input;
//     while (*ptr)
//     {
//         while (ft_skip_space(*ptr))
//         {
//             ptr++;
//         }
//         if (*ptr)
//         {
//             start = ptr;
//             while (*ptr && !ft_skip_space(*ptr))
//                 ptr++;
//             len = ptr - start;
//             result[idx] = malloc((len + 1) * sizeof(char));
//             if (result[idx] == NULL)
//             {
//                 free_split_string_on_error(result, idx);
//                 return (NULL);
//             }
//             ft_strncpy(result[idx], start, len);
//             if (*ptr && ft_skip_space(*ptr))
//             {
//                 while (ft_skip_space(*ptr))
//                     ptr++;
//                 if (*ptr == '\0')
//                 {
//                     state->check_last_space = 1;
//                     result[idx][len] = '\0';
//                 }
//                 else
//                 {
//                     state->check_last_space = 0;
//                     result[idx][len] = '\0';
//                 }
//             }
//             else
//                 result[idx][len] = '\0';
//             idx++;
//         }
//     }
//     result[idx] = NULL;
//     return (result);
// }