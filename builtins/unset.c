/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:02:05 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/21 21:08:19 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_token *token, t_data *data)
{
	int	i;
	int r;

	r = 0;
	i = 0;
	while (i < token->args_count)
	{
		if (!is_valid_identifier(token->args[i]))
			r = print_export_error(token->args[i], "unset");
		else
			delete_env_var(&data->envs, token->args[i]);
		i++;
	}
	return (r);
}
