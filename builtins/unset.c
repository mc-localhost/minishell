/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:02:05 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/14 22:06:21 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	unset(t_token *token, t_data *data)
{
	int i;

	i = 0;
	while (i < token->args_count)
	{
		delete_env_var(&data->envs, token->args[i]);
		i++;
	}
	return (1);
}
