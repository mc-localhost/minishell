/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/19 16:31:42 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_global(void)
{
	g_global.last_exit_code = 0;
	g_global.garbage_list = NULL; //only used by parsing for now
	g_global.heredoc_running = 0;
	g_global.kill_heredoc = 0;
	g_global.cmd_running = 0;
}

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

static void	tokens_cleanup(t_data *data)
{
	free_all();
	//printf("cleaned tokens\n");
	unlink(HEREDOC_FILENAME);
	//printf("cleaned heredoc\n");
	data->input = NULL;
	data->tokens = NULL;
	data->final_tokens = NULL;
	data->num_pipes = 0;
}

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
	setup_signals();
	active = 1;
	while (active == 1)
	{
		//g_global.cmd_running = 1;
		// input = readline(PROMPT);
		// g_global.cmd_running = 0;

		//START for tester
		//to install tester
		//	bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)" 
		//to run
		//	mstest
		if (isatty(fileno(stdin)))
		{
			g_global.cmd_running = 1;
			input = readline(PROMPT);
			g_global.cmd_running = 0;
		}
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
			data.input_copy = ft_strdup_safe(input);
			if (parse(&data) == EXIT_FAILURE)
			{
				free(input);
				tokens_cleanup(&data);
				continue ;
			}
			iterate_final_tokens(&data, execute); //execution
		}
		free(input);
		tokens_cleanup(&data);
	}
	return (EXIT_SUCCESS);
}
