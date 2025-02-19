/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:45:50 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*

Handle ctrl-C (SIGINT), ctrl-D (EOF) and ctrl-\ (SIGQUIT) which should behave like in bash.

In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.

ctrl-C in an empty prompt should display a new line with a new prompt.
ctrl-C in a prompt should display a new line with a new prompt.

ctrl-\ in an empty prompt should not do anything.
ctrl-\ in a prompt should not do anything.

ctrl-D in an empty prompt should quit minishell
ctrl-D in a prompt should not do anything.

The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.
Try ctrl-C,D,\ after running a blocking command like cat without arguments or grep “something“.
*/

void	ctrl_c(int sig)
{
	(void)sig;

	g_global.last_exit_code = 1;
	if (g_global.heredoc_running)
		g_global.kill_heredoc = 1;
	if (g_global.cmd_running)
	{
		printf("\n");
		//kill processes
		//free_all, unlink heredoc etc.
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
