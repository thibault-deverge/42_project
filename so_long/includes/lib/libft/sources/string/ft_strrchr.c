/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 01:38:23 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:29:08 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	char_c;

	i = ft_strlen(s) - 1;
	char_c = c;
	if (char_c == '\0')
		return ((char *)&s[i + 1]);
	while (i >= 0)
	{
		if (s[i] == char_c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
