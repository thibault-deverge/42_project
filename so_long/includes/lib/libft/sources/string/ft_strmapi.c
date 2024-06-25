/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 23:07:29 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:28:45 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*new_s;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = (*f)(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return ((char *)new_s);
}
