/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:48:15 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:27:54 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

static unsigned int	strs_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	strs;

	i = 0;
	strs = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		strs++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] == c && c != '\0')
			i++;
	}
	return (strs);
}

static unsigned int	strlen_sep(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**free_all(char **s, unsigned int j)
{
	unsigned int	i;

	i = 0;
	while (i <= j)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*str_alloc(char const *s, char c)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (strlen_sep(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**arr;

	i = 0;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (strs_count(s, c) + 1));
	if (!arr || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			arr[j] = str_alloc(&s[i], c);
			if (!arr[j])
				return (free_all(arr, j));
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
	}
	arr[j] = 0;
	return (arr);
}
