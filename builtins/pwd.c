/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:47:10 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/21 23:37:28 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_data *data)
{
	char	*cwd;

	cwd = find_env_var(&data->envs, "PWD");
	if (!cwd)
	{
		perror("pwd error");
		return (1);
	}
	else
		printf("%s\n", cwd);
	return (0);
}
