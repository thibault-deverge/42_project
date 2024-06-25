/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:33:32 by tdeverge          #+#    #+#             */
/*   Updated: 2022/11/13 17:29:35 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!*lst || !new)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
