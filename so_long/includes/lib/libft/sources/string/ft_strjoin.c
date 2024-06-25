/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:10:43 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:28:11 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*pt_newstr;
	size_t			s1_len;
	size_t			s2_len;
	size_t			total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	pt_newstr = (char *)malloc(total_len + 1);
	if (!pt_newstr)
		return (NULL);
	ft_strlcpy(pt_newstr, s1, s1_len + 1);
	ft_strlcat(pt_newstr, s2, total_len + 1);
	return (pt_newstr);
}
