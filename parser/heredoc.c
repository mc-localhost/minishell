
#include "../includes/minishell.h"

// .tmp_heredoc_file - store as value for TOKEN_HEREDOC
//delimeter doesn't get expanded, quotes get removed
//all quotes inside input are saved, 
//expansions applied if the delim is not in quotes
//delim cannot contain spaces ("    EOF" won't work)

// static void create_heredoc_file()
// {
// 	int fd;

// 	fd = open()
// }

// void handle_heredoc()
// {
// 	readline("> ");

// }