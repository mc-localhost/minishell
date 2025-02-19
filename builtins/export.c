/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 15:51:44 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_env_list(t_env_node *current)
{
	while (current)
	{
		if (current->key && current->value)
		{
			if (ft_strlen(current->value) > 0)
				printf("declare -x %s=\"%s\"\n", current->key, current->value);
			else
				printf("declare -x %s\n", current->key);
		}
		current = current->next;
	}
}

int	export(t_token *token, t_data *data)
{
	int		i;
	char	**a;

	i = 0;
	if (token->args_count > 0)
	{
		while (i < token->args_count)
		{
			if (ft_strchr(token->args[i], '='))
			{
				a = ft_split(token->args[i], '=');
				if (!a)
					return (-1);
				if (find_env_var(&data->envs, a[0]) != NULL)
					change_env_var(&data->envs, a[0], a[1]);
				else
					add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
							ft_strdup(a[1])));
				free_arr(a);
			}
			else if (find_env_var(&data->envs, token->args[i]) == NULL)
				add_env_var(&data->envs, create_env_var(ft_strdup(token->args[i]),ft_strdup("")));
			i++;
		}
	}
	else
		export_env_list(data->envs);
	return (1);
}
