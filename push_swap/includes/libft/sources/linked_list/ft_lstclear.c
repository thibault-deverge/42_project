/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:21:25 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:25:13 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

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
