/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:07:22 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/23 12:07:37 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	envp_to_list(t_data *data, char **envp, int i)
{
	t_env_node	*env_list;
	char		*equal_sign;
	size_t		key_len;
	char		*key;
	char		*value;

	env_list = NULL;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		key_len = equal_sign - envp[i];
		key = malloc((key_len + 1) * sizeof(char));
		ft_strlcpy(key, envp[i], key_len + 1);
		value = ft_strdup(equal_sign + 1);
		add_env_var(&env_list, create_env_var(key, value));
		i++;
	}
	data->envs = env_list;
}
