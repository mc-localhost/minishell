/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 14:22:46 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void init_global(void)
{
	g_last_exit_code = 0;
	g_garbage_list = NULL;
}

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	int		active;

	// atexit(&leaks);
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments.\n");
		exit(EXIT_FAILURE);
	}
	init_global();
	ft_memset(&data, 0, sizeof(data));
	envp_to_list(&data, envp, 0);
	active = 1;
	while (active == 1)
	{
		// input = readline(PROMPT);
		
		//START for tester
		//to install tester
		//	bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)" 
		//to run
		//	mstest
		if (isatty(fileno(stdin)))
			input = readline(PROMPT);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		//END for tester - remove it all before submitting

		if (*input)
		{
			add_history(input);
			data.input = input;
			data.input_copy = ft_strdup(input); //needs safe malloc
			parse(&data);
			free(data.input_copy);
		}

		//change to iterate_final_tokens(data, execute_function)
		t_token *current = data.final_tokens;
		while (current) 
		{
			if (current->type == TOKEN_BUILTIN)
			{
				if (handle_builtin(current, &data) == 999999)
				{
					active = 0;
					break;
				}
			}
			// else if (current->type == TOKEN_CMD)
			// 	execvp(current->value, current->args);
			current = current->next;
		}
		//

		free(input);
		//clean tokens and final tokens after execution
		//delete heredoc file
	}
	// free_all();
	return (EXIT_SUCCESS);
}
