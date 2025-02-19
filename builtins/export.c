/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:19:20 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 19:57:59 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_valid_identifier(const char *str)
{
    if (str == NULL || str[0] == '\0')
		return 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	int i = 1;
	while (str[i] != '\0') {
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

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

void	export_env_list_sorted(t_env_node *current)
{
	t_env_node	*sorted_list;

	sorted_list = copy_env_list(current);
	sort_env_list(sorted_list);
	export_env_list(sorted_list);
	free_env_list(sorted_list);
}

int print_export_error(char *identifier)
{
	int i;

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

int	export(t_token *token, t_data *data)
{
	int		i;
	char	**a;
	int		r;

	i = 0;
	r = 1;
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
				else if (is_valid_identifier(a[0]))
					add_env_var(&data->envs, create_env_var(ft_strdup(a[0]),
							ft_strdup(a[1])));
				else
					r = print_export_error(token->args[i]);
				free_arr(a);
			}
			else if (find_env_var(&data->envs, token->args[i]) == NULL)
				add_env_var(&data->envs,
					create_env_var(ft_strdup(token->args[i]), ft_strdup("")));
			i++;
		}
	}
	else
		export_env_list_sorted(data->envs);
	return (r);
}
