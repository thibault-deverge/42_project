/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:31:29 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:29:01 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;

	i = 0;
	little_len = ft_strlen(little);
	if (!big && len == 0)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			if (!ft_strncmp((char *)&big[i], (char *)little, little_len))
			{
				if (i + little_len <= len)
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (0);
}
