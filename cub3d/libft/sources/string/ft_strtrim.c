/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:57:36 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/27 14:18:44 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

/*
 * @summary: - make hash table for 'set' string
 * @return:  - hash table updated with 'set' value
*/
static void	hash_ascii(char *hash, char const *set)
{
	size_t	i;

	i = 126;
	while (i)
		hash[i--] = 0;
	while (set[i])
	{
		hash[(int)set[i]]++;
		i++;
	}
}

/*
 * @summary: - trim beginning of 's1' with hash table
 * @return:  - index of beginning once 's1' is trimmed
*/
static size_t	start_idx(char const *s1, char *hash)
{
	size_t	i;

	i = 0;
	while (s1[i] && hash[(int)s1[i]])
		i++;
	return (i);
}

/*
 * @summary: - trim end of 's1' with hash table
 * @return:  - index of end  once 's1' is trimmed
*/
static size_t	end_idx(char const *s1, char *hash, size_t start)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > start && hash[(int)s1[i - 1]])
		i--;
	return (i);
}

/*
 * @summary: - allocate a new string trimmed with the 'set' characters
 * @return:  - the new string trimmed 
 *
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char			hash[127];
	char			*s1_trim;
	size_t			i;
	size_t			start;
	size_t			end;

	i = 0;
	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
	{
		s1_trim = ((char *)malloc(1));
		s1_trim[0] = '\0';
		return (s1_trim);
	}
	hash_ascii(hash, set);
	start = start_idx(s1, hash);
	end = end_idx(s1, hash, start);
	s1_trim = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!s1_trim)
		return (NULL);
	while (start < end)
		s1_trim[i++] = s1[start++];
	s1_trim[i] = '\0';
	return (s1_trim);
}
