/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 15:10:56 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_env_list(t_env_node *current)
{
	while (current)
	{
		if (current->key && current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
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
					// use ft_split_safe or free manually
				if (!a)
					return (-1);
				if (find_env_var(&data->envs, a[0]) != NULL)
					change_env_var(&data->envs, a[0], a[1]);
				else
					add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
							ft_strdup(a[1])));
						// change to safe or free manually
				free_arr(a);
			}
			i++;
		}
	}
	else
		export_env_list(data->envs);
	return (1);
}
