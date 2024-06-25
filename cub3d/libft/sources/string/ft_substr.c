/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:54:17 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/27 03:32:00 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

static size_t	count_memory(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (i);
	while (s[start + i] && i < len && s[start + i] != '\n')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pt_new;
	size_t	alloc_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	alloc_len = count_memory(s, start, len);
	pt_new = (char *)malloc(sizeof(char) * alloc_len + 1);
	if (!pt_new)
		return (NULL);
	while (i < alloc_len)
		pt_new[i++] = s[start++];
	pt_new[i] = '\0';
	return (pt_new);
}
