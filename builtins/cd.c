/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:13 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/14 18:31:26 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(t_token *token)
{
	if (token->args_count > 1)
	{
		printf("cd: string not in pwd: %s\n", token->args[0]);
		return (0);
	}
	else if (chdir(token->args[0]) == 0)
	{
	 	printf("\nOK ");
	}
	else
	{
	 	printf("cd: no such file or directory: %s\n", token->args[0]);
		return (0);
	}
		// if (getcwd(cwd, sizeof(cwd)) != NULL) {
		// 	printf("%s\n", cwd);
		// } else {
		// 	printf("getcwd() error");
		// }
	return (1);
}
