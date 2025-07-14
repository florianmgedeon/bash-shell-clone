/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:02:36 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/10 14:34:38 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	trim_start(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i] && inset(s[i], set))
		i++;
	return (i);
}

static size_t	trim_end(char const *s, char const *set)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0 && inset(s[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimstart;
	size_t	trimend;
	size_t	trimlength;
	size_t	i;
	char	*trimmedstr;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	trimstart = trim_start(s1, set);
	trimend = trim_end(s1, set);
	if (trimstart > trimend)
		return (ft_strdup(""));
	trimlength = trimend - trimstart;
	trimmedstr = (char *)malloc(trimlength + 1);
	if (!trimmedstr)
		return (NULL);
	while (i < trimlength)
	{
		trimmedstr[i] = s1[trimstart + i];
		i++;
	}
	trimmedstr[i] = '\0';
	return (trimmedstr);
}
