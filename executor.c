/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 16:17:45 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_token *token, t_data *data)
{
	if (token->type == TOKEN_BUILTIN)
	{
		if (handle_builtin(token, data) == 999999)
		{
			// active = 0; //should go somewhere in data
			printf("exit\n");
		}
	}
	else if (token->type == TOKEN_CMD)
		print_token(token, data);
		// execvp(token->value, token->args); //forbidden, just for testing
}
