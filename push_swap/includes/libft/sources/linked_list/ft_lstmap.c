/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:05:43 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:25:51 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*current_node;

	if (!lst || !f || !del)
		return (NULL);
	first_node = ft_lstnew((*f)(lst->content));
	if (!first_node)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		current_node = ft_lstnew((*f)(lst->content));
		if (!current_node)
			ft_lstclear(&first_node, del);
		ft_lstadd_back(&first_node, current_node);
		lst = lst->next;
	}
	return (first_node);
}
