/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:11:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 04:02:45 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_q_string(t_token_type type)
{
	if (type == TOKEN_STRING_SINGLQ || type == TOKEN_STRING_DOUBLEQ)
		return (1);
	return (0);
}

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
	char	*builtins[7];

	num_builtins = 7;
	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "exit";
	i = 0;
	while (i < num_builtins)
	{
		if (!ft_strcmp(token->value, builtins[i])
			|| (ft_strlen(token->value) == 4 && ist_echo(token->value))
			|| (ft_strlen(token->value) == 3 && ist_env(token->value)))
		{
			token->type = TOKEN_BUILTIN;
			break ;
		}
		i++;
	}
}

t_token	*init_current_cmd(void)
{
	t_token	*current_cmd;

	current_cmd = init_token();
	current_cmd->type = TOKEN_CMD;
	current_cmd->redirections_in = NULL;
	current_cmd->redirections_out = NULL;
	return (current_cmd);
}
