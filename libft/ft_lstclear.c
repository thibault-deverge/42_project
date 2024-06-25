/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:21:25 by tdeverge          #+#    #+#             */
/*   Updated: 2022/10/09 23:43:33 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	**current_node;
	t_list	*next_node;

	if (!del || !lst || !*lst)
		return ;
	current_node = lst;
	next_node = *lst;
	while (current_node && *current_node)
	{
		next_node = (*current_node)->next;
		ft_lstdelone(*current_node, del);
		*current_node = next_node;
	}
}
