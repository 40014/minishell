#include "minishell.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static char	*lenght_word(const char **s, char c)
{
	int		word_len;
	char	*word;
	int		j;

	while (**s == c)
		(*s)++;
	word_len = 0;
	while ((*s)[word_len] && (*s)[word_len] != c)
		word_len++;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (j < word_len)
	{
		word[j] = (*s)[j];
		j++;
	}
	word[word_len] = '\0';
	*s = *s + word_len;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	int		num_words;
	int		i;
	char	**result;

	if (s == NULL)
		return (NULL);
	num_words = count_words(s, c);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		result[i] = lenght_word(&s, c);
		if (result[i] == NULL)
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[num_words] = NULL;
	return (result);
}
