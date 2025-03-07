/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/27 09:57:26 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_env_list_sorted(t_env_node *current)
{
	t_env_node	*env;
	t_env_node	*env_copy;

	if (!current)
		return (0);
	env = copy_env_list(current);
	env_copy = env;
	sort_env_list(env);
	while (env)
	{
		if (env->key && env->value)
		{
			if (ft_strlen(env->value) > 0)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s=\"\"\n", env->key);
		}
		else if (env->key && !env->value)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	free_env_list(env_copy);
	return (0);
}

int	upd_env(char *token, t_data *data)
{
	char	**a;

	a = ft_split(token, '=');
	if (!a)
	{
		if (!is_valid_identifier(token))
			return (print_export_error(token, "minishell: export"));
		return (1);
	}
	if (a[0] && if_env_var(&data->envs, a[0]))
		change_env_var(&data->envs, a[0], a[1]);
	else if (a[0] && is_valid_identifier(a[0]))
		add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
				ft_strdup(a[1])));
	else if (!is_valid_identifier(a[0]))
		return (free_arr(a), print_export_error(token, "minishell: export"));
	free_arr(a);
	return (0);
}

int	emty_env_var(char *token, t_data *data)
{
	if (!is_valid_identifier(token))
		return (print_export_error(token, "export"));
	add_env_var(&data->envs, create_env_var(ft_strdup(token), NULL));
	return (0);
}

int	export_plus(char *token, t_data *data)
{
	char	**arr;
	char	*key;
	char	*oldval;
	char	*newval;

	arr = ft_split(token, '=');
	if (arr[0] && arr[0][ft_strlen(arr[0]) - 1] == '+'
		&& arr[0][ft_strlen(arr[0]) - 2] != '+')
	{
		key = ft_strtrim(arr[0], "+");
		newval = NULL;
		oldval = find_env_var(&data->envs, key);
		if (!if_env_var(&data->envs, key))
			emty_env_var(key, data);
		if (arr[1])
		{
			newval = ft_strjoin(oldval, arr[1]);
			change_env_var(&data->envs, key, newval);
			free(newval);
		}
		free(key);
	}
	else
		return (free_arr(arr), print_export_error(token, "export"));
	return (free_arr(arr), 0);
}

int	export(t_token *token, t_data *data)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (token->args_count > 0)
	{
		while (i[0] < token->args_count)
		{
			if (ft_strchr(token->args[i[0]], '+')
				&& ft_strchr(token->args[i[0]], '='))
				i[1] = export_plus(token->args[i[0]], data);
			else if (ft_strchr(token->args[i[0]], '=')
				&& ft_strlen(token->args[i[0]]) > 1)
				i[1] = upd_env(token->args[i[0]], data);
			else if (!if_env_var(&data->envs, token->args[i[0]]))
				i[1] = emty_env_var(token->args[i[0]], data);
			if (i[1] != 0)
				i[2] = i[1];
			i[0]++;
		}
	}
	else
		i[2] = export_env_list_sorted(data->envs);
	return (i[2]);
}
