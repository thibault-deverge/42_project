/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:07:38 by tdeverge          #+#    #+#             */
/*   Updated: 2023/01/22 18:11:15 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * @summary:
 * 		- Split the argv corresponding to the command we want to execute.
 * 		- Return a 2d array with the command at index 0 and arguments on
 * 		the next indexes.
*/
char	**ft_find_command(char **paths, char **argv, int child_index)
{
	char	**cmd_args;

	cmd_args = ft_split(argv[child_index + 2], ' ');
	if (!cmd_args)
	{
		free(paths);
		throw_perror(EXIT_ALLOC);
	}
	return (cmd_args);
}

/*
 * @summary:
 * 		- Search in the 'envp' 2d array the entry for the PATH variable
 * 		and return it.
*/
char	**ft_find_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		throw_perror(EXIT_ALLOC);
	return (paths);
}

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
