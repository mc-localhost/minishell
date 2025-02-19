/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:54:10 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 18:06:17 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to create a deep copy of the original environment list
t_env_node	*copy_env_list(t_env_node *original)
{
	t_env_node	*copy_head;
	t_env_node	*copy_tail;
	t_env_node	*new_node;

	copy_head = NULL;
	copy_tail = NULL;
	while (original)
	{
		new_node = (t_env_node *)malloc(sizeof(t_env_node));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(original->key);
		new_node->value = ft_strdup(original->value);
		new_node->next = NULL;
		if (!copy_head) {
	    	copy_head = new_node;
	    	copy_tail = new_node;
	    }
		else
		{
			copy_tail->next = new_node;
			copy_tail = new_node;
	    }
	    original = original->next;
	}
	return (copy_head);
}

// Function to swap two nodes in the list (used for sorting)
void	swap_nodes(t_env_node *a, t_env_node *b)
{
	char *temp_key;
	char *temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void sort_env_list(t_env_node *head)
{

	int			swapped;
	t_env_node	*ptr1;
	t_env_node	*ptr2;

	ptr2 = NULL;
	swapped = 1;
	while (swapped)
	{
	    swapped = 0;
	    ptr1 = head;
	    while (ptr1->next != ptr2) {
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
}

// Function to free the environment list
void free_env_list(t_env_node *head)
{
	t_env_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

// Function to print the environment list, sorted by key
void	print_env_list_sorted(t_env_node *current)
{
	t_env_node *sorted_list;

	sorted_list = copy_env_list(current);
	sort_env_list(sorted_list);
	while (sorted_list)
	{
		if (sorted_list->key && sorted_list->value)
			printf("%s=%s\n", sorted_list->key, sorted_list->value);
		sorted_list = sorted_list->next;
	}
	free_env_list(sorted_list);
}

void	print_env_list(t_env_node *current)
{
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
