/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:36:24 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/25 17:02:47 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_allocation(void *ptr)
{
	t_alloc_node	*new_node;

	new_node = malloc(sizeof(t_alloc_node));
	if (!new_node)
	{
		perror("safe_malloc failed when adding to list");
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->next = g_garbage_list; //technically prev, not next. but doesn't matter i guess
	g_garbage_list = new_node;
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("safe_malloc failed");
		exit(EXIT_FAILURE);
	}
	add_allocation(ptr);
	return (ptr);
}

void	free_all(void)
{
	t_alloc_node	*current;
	t_alloc_node	*tmp;

	current = g_garbage_list;
	while (current)
	{
		free(current->ptr);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	g_garbage_list = NULL;
}
