/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:47:10 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/19 18:40:57 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_data *data)
{
	char	*cwd;

	cwd = find_env_var(&data->envs, "PWD");
	if (!cwd)
		perror("pwd error"); // to replace with better error handling
	else
		printf("%s\n", cwd);
}
