/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:19:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/26 19:20:11 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*find_env_var(t_env_node **head, const char *str)
{
	t_env_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env_node	*create_env_var(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_var(t_env_node **head, t_env_node *new_node)
{
	t_env_node	*temp;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	delete_env_var(t_env_node **head, const char *key)
{
	t_env_node	*temp;
	t_env_node	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				*head = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	change_env_var(t_env_node **head, const char *key, const char *value)
{
	t_env_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
}
