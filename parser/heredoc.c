/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:14:06 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:11:18 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
When << is found in input it is first parsed as
redirection of type TOKEN_HEREDOC.
Heredoc handler reads user input line by line before specified delimeter
and writes everything into a temporary heredoc file.

If delimeter is quoted (' or "), nothing inside heredoc gets expanded.

bash-3.2$ cat << "don't expand"
> $USER stays $USER
> don't expand
$USER stays $USER

Delimeter itself doesn't get expanded. But everything inside is,
no matter the quotations.

bash-3.2$ cat << $USER
> some text
> 'some text with $USER'
> $USER
some text
'some text with vvasiuko'
*/

static int to_expand_value(t_token_type type)
{
	int	to_expand;

	to_expand = 1;
	if (type != TOKEN_STRING)
		to_expand = 0;
	return (to_expand);
}

char	*handle_heredoc(t_token *token, t_data *data)
{
	char	*delim;
	char	*input;
	int		to_expand;
	int		fd;

	delim = token->value;
	fd = open(HEREDOC_FILENAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	to_expand = to_expand_value(token->type);
	g_global.heredoc_running = 1;
	input = readline(HEREDOC_PROMPT);
	while (input && ft_strcmp(input, delim) && !g_global.kill_heredoc)
	{
		if (to_expand)
			input = expand(input, data);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		if (!to_expand)
			free(input);
		input = readline(HEREDOC_PROMPT);
	}
	if (input)
		free(input);
	close(fd);
	g_global.heredoc_running = 0;
	return (HEREDOC_FILENAME);
}
