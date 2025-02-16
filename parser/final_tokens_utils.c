/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:11:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 18:12:33 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_string(t_token_type type)
{
	if (type == TOKEN_STRING || type == TOKEN_STRING_SINGLQ
		|| type == TOKEN_STRING_DOUBLEQ)
		return (1);
	return (0);
}

void	builtin_token(t_token *token)
{
	int		i;
	int		num_builtins;
	char	*builtins[9];

	num_builtins = 9;
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "exit";
	builtins[7] = "clear";
	builtins[8] = "cls";
	i = 0;
	while (i < num_builtins)
	{
		if (!ft_strcmp(token->value, builtins[i]))
		{
			token->type = TOKEN_BUILTIN;
			break ;
		}
		i++;
	}
}
