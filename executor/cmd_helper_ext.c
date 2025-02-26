/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:19:07 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/26 19:23:32 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Joins key and value into a single string "key=value"
char	*join_key_value(char *key, char *value)
{
	char	*result;
	char	*final_result;

	result = ft_strjoin(key, "=");
	if (!result)
		return (NULL);
	final_result = ft_strjoin(result, value);
	free(result);
	return (final_result);
}

int	is_directory(const char *path)
{
	DIR	*dir;

	if (ft_strcmp(path, ".") || ft_strcmp(path, ".."))
		return (1);
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}

int	if_env_var(t_env_node **head, const char *str)
{
	t_env_node	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

// Counts valid nodes in the linked list
int	count_nodes(t_env_node *current)
{
	int	len;

	len = 0;
	while (current)
	{
		if (current->key && current->value)
			len++;
		current = current->next;
	}
	return (len);
}
