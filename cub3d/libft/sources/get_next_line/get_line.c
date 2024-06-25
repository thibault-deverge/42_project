/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:22:43 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/04/16 21:10:57 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

static void	ft_lstclear(t_list *lst)
{
	t_link	*tmp;

	tmp = lst->first;
	while (lst->first != NULL)
	{
		tmp = tmp->next;
		free(lst->first->content);
		free(lst->first);
		lst->first = tmp;
	}
}

static t_list	*ft_linkadd(t_list *lst, char *buffer)
{
	t_link	*new;
	t_link	*tmp;

	new = malloc(sizeof(t_link));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char) * 2);
	if (!new)
		return (NULL);
	new->content[0] = '\0';
	new->content = ft_strcat(new->content, buffer);
	new->next = NULL;
	if (lst->first == NULL)
		lst->size = 0;
	if (lst->first == NULL)
		lst->first = new;
	else
	{
		tmp = lst->first;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	lst->size += 1;
	return (lst);
}

static char	*ft_fill(t_list *lst)
{
	char	*line;
	t_link	*tmp;	

	if (!lst->first)
		return (NULL);
	tmp = lst->first;
	line = malloc(sizeof(char) * ((lst->size) + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (tmp != NULL)
	{
		line = ft_strcat(line, tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(lst);
	return (line);
}

static char	*ft_read_line(int fd, char *buffer)
{
	int	len;

	len = read(fd, buffer, 1);
	if (len < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[len] = '\0';
	return (buffer);
}

char	*ft_get_line(int fd)
{
	char		*buffer;
	char		*line;
	t_list		lst;

	lst.first = NULL;
	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	buffer[0] = ' ';
	while (buffer[0] != '\n' && buffer[0] != '\0')
	{
		buffer = ft_read_line(fd, buffer);
		if (buffer == NULL)
			return (NULL);
		else if (buffer[0] != '\0')
			ft_linkadd(&lst, buffer);
	}
	free(buffer);
	line = ft_fill(&lst);
	return (line);
}
