/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sepjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:18:29 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/02/13 01:11:53 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Copy one string into another one in memory.
*/
static char	*ft_strcpy(char *dest, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
 * @summary:
 * 		- Concatenate 'str' with 'dest' received as parameter with
 * 		character 'c' at beginning.
*/
static char	*ft_strcat(char *dest, char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	dest[i] = c;
	i++;
	while (str[j])
	{
		dest[i + j] = str[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/*
 * @summary:
 * 		- Join both strings received as parameter with character c 
 * 		also received as parameter between them.
*/
char	*ft_sepjoin(char const *s1, char const *s2, char c)
{
	size_t		len;
	char		*dest;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s1);
	ft_strcat(dest, s2, c);
	return (dest);
}
