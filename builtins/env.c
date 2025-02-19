/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:56:43 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 18:51:32 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtoupper(char *str) // don't need this
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

int	env_cmd_error(t_token *token)
{
	ft_putstr_stderr("env: ");
	ft_putstr_stderr(token->args[0]);
	ft_putstr_stderr(": No such file or directory\n");
	return (-1);
}

// Function to print the environment list, sorted by key
void	print_env_list_sorted(t_env_node *current)
{
	t_env_node	*sorted_list;

	sorted_list = copy_env_list(current);
	bash_sort_env_list(sorted_list);
	while (sorted_list)
	{
		if (sorted_list->key && sorted_list->value)
			printf("%s=%s\n", sorted_list->key, sorted_list->value);
		sorted_list = sorted_list->next;
	}
	free_env_list(sorted_list);
}

int	env(t_token *token, t_data *data)
{
	if (token->args_count == 1 && !ft_strchr(token->args[0], '='))
	{
		if (find_env_var(&data->envs, ft_strtoupper(token->args[0])) != NULL)
			printf("%s\n", find_env_var(&data->envs,
					ft_strtoupper(token->args[0])));
		else
			return (env_cmd_error(token));
	}
	else if (token->args_count > 1)
		return (env_cmd_error(token));
	else
		print_env_list_sorted(data->envs);
	if (token->args_count == 1 && ft_strchr(token->args[0], '='))
		printf("%s\n", token->args[0]);
	return (1);
}
