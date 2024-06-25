/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:09:53 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/02 12:45:09 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_cast;
	unsigned char	*s2_cast;
	size_t			i;

	i = 0;
	s1_cast = (unsigned char *)s1;
	s2_cast = (unsigned char *)s2;
	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (0);
	while (s1_cast[i] != '\0' && i < n)
	{
		if (s1_cast[i] != s2_cast[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return (s1_cast[i] - s2_cast[i]);
}
