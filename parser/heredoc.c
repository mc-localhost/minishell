
#include "../includes/minishell.h"

//delimeter doesn't get expanded, quotes get removed
//all quotes inside input are saved

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