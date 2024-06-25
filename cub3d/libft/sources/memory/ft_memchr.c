/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:26 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:26:41 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cast;
	unsigned char	c_cast;
	size_t			i;

	i = 0;
	s_cast = (unsigned char *)s;
	c_cast = (unsigned char)c;
	while (i < n)
	{
		if (s_cast[i] == c_cast)
			return (&s_cast[i]);
		i++;
	}
	return (NULL);
}
