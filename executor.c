/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:15 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_token *token, t_data *data)
{
	if (token->type == TOKEN_BUILTIN)
	{
		handle_builtin(token, data);
		// active = 0; //should go somewhere in data or be global
	}
	else if (token->type == TOKEN_CMD)
		printf("read cmd\n");
		// print_token(token, data);
		// execvp(token->value, token->args); //forbidden, just for testing
}
