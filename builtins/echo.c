/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:55 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 16:22:48 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	echo_n(t_token *token)
{
	int	i;

	i = 1;
	while (i < token->args_count - 1)
	{
		printf("%s ", token->args[i]);
		i++;
	}
	printf("%s", token->args[i]);
	return (0);
}

int	echo(t_token *token)
{
	int	i;

	if (token->args_count > 0)
	{
		if (!ft_strcmp(token->args[0], "-n")) //replace with whole string check
			return (echo_n(token));
		else
		{
			i = 0;
			while (i < token->args_count - 1)
			{
				printf("%s ", token->args[i]);
				i++;
			}
			printf("%s\n", token->args[i]);
		}
	}
	return (0);
}
