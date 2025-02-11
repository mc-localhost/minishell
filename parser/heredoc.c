
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

char *handle_heredoc(t_token *token, t_data *data)
{
	char *delim;
	char *input;
	char *filename;
	int to_expand;
	int fd;

	delim = token->value; 
	//delim cannot contain spaces ("    EOF" won't work) - FIX!
	filename = ".heredoc_file_SOME_ID"; //figure out a name specific for the command
	//create and open file, if exists -> write a new one
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	to_expand = 1;
	if (token->type != TOKEN_STRING) //means there were quotes and we should not expand $
		to_expand = 0;
	input = readline(HEREDOC_PROMPT);
	while (input && ft_strcmp(input, delim))
	{
		if (to_expand)
			input = expand(input, data);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline(HEREDOC_PROMPT);
	}
	free(input);
	close(fd);
	return (filename);
}