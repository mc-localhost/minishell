/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 11:33:47 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* char **builtins;

echo, echo -n 	= print all args, add '\n' in the end if there is no -n flag
cd				= chdir(path)
pwd				= printf(getcwd())
env				= print_env_list(data.envs);
export			= change_env_var(&data.envs, "VAR_NAME", "NEW VALUE");
unset			= delete_env_var(&data.envs, "VAR_NAME");
exit			= exit(status)

*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments.\n");
		exit(EXIT_FAILURE);
	}

	g_garbage_list = NULL;
	ft_memset(&data, 0, sizeof(data));

	envp_to_list(&data, envp, 0);
	printf("\n parsed env vars\n");
	print_env_list(data.envs);
	printf("**********************\n");

	change_env_var(&data.envs, "USER", "changed");
	printf("\n changed USER var\n");
	print_env_list(data.envs);
	printf(" **********************\n");

	delete_env_var(&data.envs, "USER");
	printf("\n deleted USER var\n");
	print_env_list(data.envs);
	printf("**********************\n");

	add_env_var(&data.envs, create_env_var("newUSER", "I'VE JUST BEEN CREATED"));
	//but what happens when the var already exists?
	printf("\n added newUSER var to the end\n");
	print_env_list(data.envs);
	printf("**********************\n");

	while (1)
	{
		//trim(input) to remove whitespaces before and after
		input = ft_strtrim(readline(PROMPT), "\t\n\v\f\r "); //change to safe_malloc?
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		printf("input: %s\n", input);
		free(input);
	}
	free_all();
	return (EXIT_SUCCESS);
}
