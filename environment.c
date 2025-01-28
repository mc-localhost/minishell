/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:19:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 13:14:35 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env_node	*create_env_var(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = safe_malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_var(t_env_node **head, t_env_node *new_node) //but what happens when a var with this key already exists?
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

//this should suffice to not print it and not check it while searching
// and the garbage collector will deal with the freeing
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
			temp->key = NULL;
			temp->value = NULL;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("no such key '%s'\n", key); // change to smth else
}

void	change_env_var(t_env_node **head, const char *key, const char *value)
{
	t_env_node	*temp;
	t_env_node	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value); // change to safe_malloc
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("no such key '%s'\n", key); // change to smth else
}

void	envp_to_list(t_data *data, char **envp, int i) // int i 'cause only 5 vars allowed
{
	t_env_node *env_list;
	char *equal_sign;
	size_t key_len;
	char *key;
	char *value;

	env_list = NULL;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		key_len = equal_sign - envp[i];
		key = safe_malloc((key_len + 1) * sizeof(char));
		ft_strlcpy(key, envp[i], key_len + 1);
		// change to safe_malloc
		value = ft_strdup(equal_sign + 1);
		// change to safe_malloc
		add_env_var(&env_list, create_env_var(key, value));
		i++;
	}
	data->envs = env_list;
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
