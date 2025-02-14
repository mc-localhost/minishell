/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:19:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/14 22:18:25 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*find_env_var(t_env_node **head, const char *str)
{
	t_env_node	*temp;

	temp = *head;
	while (temp)
	{
		// printf("comparing %s with %s\n", temp->key, str);
		if (ft_strcmp(temp->key, str) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

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
void delete_env_var(t_env_node **head, const char *key)
{
	t_env_node *temp = *head;
	t_env_node *prev = NULL;

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
            return;
        }
        prev = temp;
        temp = temp->next;
    }
	// write(STDERR_FILENO, "No such key: ", 13);//I don't think we need to output anythig here as bash don't do this
	// write(STDERR_FILENO, key, strlen(key));
	// write(STDERR_FILENO, "\n", 1);
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
			temp->value = ft_strdup(value); // change to safe_malloc
			return ;
		}
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
