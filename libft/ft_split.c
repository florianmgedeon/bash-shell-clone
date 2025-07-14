/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:39:07 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:33:36 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_sep(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

static int	count_str(const char *str, char c)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_sep(str[i], c))
			i++;
		if (str[i] != '\0')
			s++;
		while (str[i] != '\0' && !is_sep(str[i], c))
			i++;
	}
	return (s);
}

/* static void	*free_strings(char **strings)
{
	int	i;

	i = 0;
	if (strings)
	{
		while (strings[i])
		{
			free(strings[i]);
			i++;
		}
		free(strings);
	}
	return (NULL);
} */

static char	*ft_word(const char *str, char c)
{
	int		wlen;
	int		i;
	char	*word;

	i = 0;
	wlen = 0;
	while (str[wlen] && !is_sep(str[wlen], c))
		wlen++;
	word = (char *)malloc(sizeof(char) * (wlen + 1));
	if (!word)
		return (NULL);
	while (i < wlen)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		words;
	char	**strings;

	i = 0;
	words = count_str(str, c);
	strings = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strings)
		return (NULL);
	while (*str != '\0')
	{
		while (*str != '\0' && is_sep(*str, c))
			str++;
		if (*str != '\0')
		{
			strings[i] = ft_word(str, c);
			if (strings[i] == NULL)
				return (ft_free_strings(strings), NULL);
			i++;
		}
		while (*str != '\0' && !is_sep(*str, c))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
/*
int main(void) 
{
    const char *input = "This is a test string,split it,please";
    char **result = ft_split(input, ',');

    if (result) {
        for (int i = 0; result[i]; i++) {
            printf("Token %d: \"%s\"\n", i + 1, result[i]);
        }
        free_strings(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
*/