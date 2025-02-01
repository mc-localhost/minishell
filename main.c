/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/01 02:35:52 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
char *builtins[] = {
  "cd",
  "pwd",
  "env",
  "export",
  "unset"
};

echo, echo -n 	= print all args, add '\n' in the end if there is no -n flag
cd				= chdir(path)
pwd				= printf(getcwd())
env				= print_env_list(data.envs);
export			= change_env_var(&data.envs, "VAR_NAME", "NEW VALUE");
unset			= delete_env_var(&data.envs, "VAR_NAME");
-----	already implemented in main, sorta	-----
exit			= exit(), do not handle options

*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	char	*trimmed;

	g_last_exit_code = 0; //remove?
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments.\n");
		exit(EXIT_FAILURE);
	}
	g_garbage_list = NULL;
	ft_memset(&data, 0, sizeof(data));
	envp_to_list(&data, envp, 0);
	// print_env_list(data.envs); //cmd = env or export
	// printf("\n**********************\n");

	// change_env_var(&data.envs, "USER", "changed"); cmd = export VAR_NAME="value"
	// printf("\n changed USER var\n");
	// print_env_list(data.envs);
	// printf(" **********************\n");

	// delete_env_var(&data.envs, "USER"); //cmd = unset VAR_NAME
	// printf("\n deleted USER var\n");
	// print_env_list(data.envs);
	// printf("**********************\n");

	// add_env_var(&data.envs, create_env_var("newUSER", "I'VE JUST BEEN CREATED")); cmd = export VAR_NAME="value"
	// //but what happens when the var already exists?
	// printf("\n added newUSER var to the end\n");
	// print_env_list(data.envs);
	// printf("**********************\n");

	//echo $MY_VAR is to print the value of MY_VAR

	while (1)
	{
		input = readline(PROMPT);
		trimmed = ft_strtrim(input, "\t\n\v\f\r ");
		if (ft_strncmp("exit", trimmed, 4) == 0)
		{
			free(trimmed);
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		printf("input: %s\n", input);
		if (ft_strcmp(input, "env") == 0 || ft_strcmp(input, "export") == 0)
			print_env_list(data.envs);
		// scan(input, &data);
		expand(input, &data);
		free(input);
	}
	free_all();
	return (EXIT_SUCCESS);
}
