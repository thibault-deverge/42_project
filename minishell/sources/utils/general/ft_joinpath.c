/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:45:14 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 02:45:43 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary: 
 * 		- Join string 's1' and 's2' with the '\' between them.
 * 		- Allow to transform the name of the command to its absolute path.
*/
char	*ft_joinpath(char const *s1, char const *s2)
{
	char			*pt_newstr;
	size_t			s1_len;
	size_t			s2_len;
	size_t			total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	pt_newstr = (char *)malloc(total_len + 1);
	if (!pt_newstr)
		return (NULL);
	ft_strlcpy(pt_newstr, s1, s1_len + 1);
	pt_newstr[s1_len] = '/';
	pt_newstr[s1_len + 1] = '\0';
	ft_strlcat(pt_newstr, s2, total_len + 1);
	return (pt_newstr);
}
