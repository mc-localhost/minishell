/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/22 22:18:04 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	export_env_list_sorted(t_env_node *current)
{
	t_env_node	*env;

	env = copy_env_list(current);
	sort_env_list(env);
	while (env)
	{
		if (env->key && env->value)
		{
			if (ft_strlen(env->value) > 0)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s\n", env->key);
		}
		env = env->next;
	}
	free_env_list(env);
	return (0);
}

int	upd_env(char *token, t_data *data)
{
	char	**a;

	a = ft_split(token, '=');
	if (!a)
		return (1);
	if (a[1] && find_env_var(&data->envs, a[0]) != NULL)
		change_env_var(&data->envs, a[0], a[1]);
	else if (a[1] && is_valid_identifier(a[0]))
		add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
				ft_strdup(a[1])));
	else if (!is_valid_identifier(a[0]))
		return (free_arr(a), print_export_error(token, "export"));
	free_arr(a);
	return (0);
}

int	emty_env_var(char *token, t_data *data)
{
	if (!is_valid_identifier(token))
		return (print_export_error(token, "export"));
	add_env_var(&data->envs, create_env_var(ft_strdup(token), ft_strdup("")));
	return (0);
}

int	export(t_token *token, t_data *data)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (token->args_count > 0)
	{
		while (i < token->args_count)
		{
			if (ft_strchr(token->args[i], '=') && ft_strlen(token->args[i]) > 1)
			{
				if (upd_env(token->args[i], data) != 0)
					r = 1;
			}
			else if (find_env_var(&data->envs, token->args[i]) == NULL)
			{
				if (emty_env_var(token->args[i], data) != 0)
					r = 1;
			}
			i++;
		}
	}
	else
		r = export_env_list_sorted(data->envs);
	return (r);
}
