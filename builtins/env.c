/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:56:43 by aelaaser          #+#    #+#             */
/*   Updated: 2025/03/07 12:58:43 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_strtoupper(char *str) // don't need this
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != '\0')
// 	{
// 		str[i] = ft_toupper(str[i]);
// 		i++;
// 	}
// 	return (str);
// }

// Function to print the environment list, sorted by key
void	print_env_list_sorted(t_env_node *current)
{
	t_env_node	*sorted_list;
	t_env_node	*env_copy;

	sorted_list = copy_env_list(current);
	env_copy = sorted_list;
	bash_sort_env_list(sorted_list);
	while (sorted_list)
	{
		if (sorted_list->key && sorted_list->value)
			printf("%s=%s\n", sorted_list->key, sorted_list->value);
		sorted_list = sorted_list->next;
	}
	free_env_list(env_copy);
}

static	int	use_env(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "-i"))
			return (0);
		i++;
	}
	return (1);
}

static char	**tmp_env(char **args)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	envp = (char **)malloc((ft_arr_size(args) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			envp[j++] = ft_strdup(args[i]);
		i++;
	}
	envp[j] = NULL;
	return (envp);
}

static void	env_exec(t_data *data, char **args, char *cmd)
{
	t_data	tmpdata;
	char	**envp;

	envp = NULL;
	ft_memset(&tmpdata, 0, sizeof(tmpdata));
	if (use_env(args))
		envp = list_to_arr(data->envs);
	else
		envp = tmp_env(args);
	if (envp)
	{
		envp_to_list(&tmpdata, envp, 0);
		free_arr(envp);
	}
	tmpdata.input = ft_strdup(cmd);
	if (parse(&tmpdata) != EXIT_FAILURE)
		execute_commands(&tmpdata);
	free_env(&tmpdata);
}

// print_env_list_sorted(data->envs);
// return (0);
int	env(t_token *token, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	g_global.last_exit_code = 0;
	if (token->args_count >= 1)
	{
		while (token->args[i])
		{
			if (ft_strcmp(token->args[i], "-i")
				&& !ft_strchr(token->args[i], '='))
			{
				if (tmp)
					tmp = ft_strjoin_safe(tmp, " ");
				tmp = ft_strjoin_safe(tmp, token->args[i]);
			}
			i++;
		}
		env_exec(data, token->args, tmp);
	}
	else
		print_env_list_sorted(data->envs);
	return (g_global.last_exit_code);
}

// if (token->args_count == 1 && !ft_strchr(token->args[0], '='))
// {
// 	if (find_env_var(&data->envs, ft_strtoupper(token->args[0])) != NULL)
// 		printf("%s\n", find_env_var(&data->envs,
// 				ft_strtoupper(token->args[0])));
// 	else
// 		return (env_cmd_error(token));
// }
// else if (token->args_count > 1)
// 	return (env_cmd_error(token));
// else
// 	print_env_list_sorted(data->envs);
// if (token->args_count == 1 && ft_strchr(token->args[0], '='))
// 	printf("%s\n", token->args[0]);
// return (0);
