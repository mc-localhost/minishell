/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 20:29:37 by aelaaser         ###   ########.fr       */
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
	return (1);
}

int	print_export_error(char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (identifier[i] == '(' || identifier[i] == ')')
		{
			ft_putstr_stderr("syntax error near unexpected token `");
			write(2, &identifier[i], 1);
			ft_putstr_stderr("'\n");
			return (-1);
		}
		i++;
	}
	ft_putstr_stderr("export: `");
	ft_putstr_stderr(identifier);
	ft_putstr_stderr("': not a valid identifier\n");
	return (-1);
}

int	upd_env(char *token, t_data *data)
{
	char	**a;

	a = ft_split(token, '=');
	if (!a)
		return (-1);
	if (find_env_var(&data->envs, a[0]) != NULL)
		change_env_var(&data->envs, a[0], a[1]);
	else
		add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
				ft_strdup(a[1])));
	free_arr(a);
	return (1);
}

int	export(t_token *token, t_data *data)
{
	int		i;
	int		r;

	i = 0;
	r = 1;
	if (token->args_count > 0)
	{
		while (i < token->args_count)
		{
			if (!is_valid_identifier(token->args[i]))
				r = print_export_error(token->args[i]);
			else if (ft_strchr(token->args[i], '='))
			{
				if (upd_env(token->args[i], data) != 1)
					r = -1;
			}
			else if (find_env_var(&data->envs, token->args[i]) == NULL)
				add_env_var(&data->envs,
					create_env_var(ft_strdup(token->args[i]), ft_strdup("")));
			i++;
		}
	}
	else
		r = export_env_list_sorted(data->envs);
	return (r);
}
