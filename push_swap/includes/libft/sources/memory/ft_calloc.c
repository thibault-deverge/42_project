/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:13:24 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:26:32 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

#define INT_MAX 2147483647

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*pt_memory;

	if (nmemb * size > INT_MAX || size > INT_MAX)
		return (NULL);
	pt_memory = malloc(nmemb * size);
	if (pt_memory)
	{
		i = 0;
		while (i < nmemb * size)
		{
			((char *)pt_memory)[i] = 0;
			i++;
		}
		return (pt_memory);
	}
	else
		return (NULL);
}
