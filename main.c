/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:59 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/23 11:44:28 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_global(void)
{
	g_global.last_exit_code = 0;
	g_global.garbage_list = NULL;
	g_global.heredoc_running = 0;
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

static void	add_level(t_data *data)
{
	char	*level;
	char	*new_level;

	level = find_env_var(&data->envs, "SHLVL");
	if (level)
	{
		new_level = ft_itoa(ft_atoi(level) + 1);
		change_env_var(&data->envs, "SHLVL", new_level);
		free(new_level);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;
	int		active;

	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments.\n");
		exit(EXIT_FAILURE);
	}
	init_global();
	ft_memset(&data, 0, sizeof(data));
	envp_to_list(&data, envp, 0);
	add_level(&data);
	setup_signals();
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
		{
			input = readline(PROMPT);
		}
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			if (!line)
				break;
			input = ft_strtrim(line, "\n");
			free(line);
		}
		//END for tester - remove it all before submitting
		if (*input)
		{
			add_history(input);
			data.input = input;
			if (parse(&data) == EXIT_FAILURE)
			{
				free(input);
				tokens_cleanup(&data);
				continue ;
			}
			g_global.cmd_running = 1;
			if (data.num_pipes >= 1)
				execute_pipeline(&data);
			else
				iterate_final_tokens(&data, execute);
			g_global.cmd_running = 0;
		}
		free(input);
		tokens_cleanup(&data);
	}
	return (g_global.last_exit_code);
}
