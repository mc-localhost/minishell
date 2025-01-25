/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:27:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/25 12:33:04 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lst_new_del(void *cnt, void *(*f)(void *))
{
	t_list	*new;

	new = ft_lstnew(NULL);
	if (new == NULL)
		return (NULL);
	new->content = f(cnt);
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	result = lst_new_del(lst->content, f);
	if (result == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		current = lst_new_del(lst->content, f);
		ft_lstadd_back(&result, current);
		lst = lst->next;
		if (current == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
	}
	return (result);
}
