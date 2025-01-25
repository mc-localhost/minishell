/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/25 17:07:10 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char **builtins;

echo, echo -n 	= print all args, add '\n' in the end if there is no -n flag
cd				= chdir(path)
pwd				= printf(getcwd())
env				= printf() all env variables
export			= change env value
unset			= remove env value
exit	exit(status)

*/


int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;

	g_garbage_list = NULL;

	envp_to_list(envp, 0);
	printf("\n parsed env vars\n");
	print_env_list(g_ast.envs);
	printf("**********************\n");

	change_env_var(&g_ast.envs, "USER", "changed");
	printf("\n changed USER var\n");
	print_env_list(g_ast.envs);
	printf(" **********************\n");

	delete_env_var(&g_ast.envs, "USER");
	printf("\n deleted USER var\n");
	print_env_list(g_ast.envs);
	printf("**********************\n");

	add_env_var(&g_ast.envs, create_env_var("newUSER", "I'VE JUST BEEN CREATED"));
	//but what happens when the var already exists?
	printf("\n added newUSER var to the end\n");
	print_env_list(g_ast.envs);
	printf("**********************\n");

	while (1)
	{
		input = readline(PROMPT);
		if (ft_strncmp("exit ", input, 5) == 0 || ft_strcmp("exit", input) == 0)
		//irl also should work if there are spaces before
			break ;
		add_history(input);
		printf("input: %s\n", input);
		free(input);
	}
	return (0);
}
