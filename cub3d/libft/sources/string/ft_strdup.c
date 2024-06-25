/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:25:05 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:28:01 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*pt_newstr;
	size_t	s_len;

	s_len = ft_strlen(s);
	pt_newstr = (char *)malloc(sizeof(char) * s_len + 1);
	if (pt_newstr)
	{
		ft_strlcpy(pt_newstr, s, s_len + 1);
		return (pt_newstr);
	}
	return (NULL);
}
