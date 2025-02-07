
#include "../includes/minishell.h"

//check if builtin function
// int num_builtins = 7;
// char *builtins[7] = {
//   "cd",
//   "echo",
//   "pwd",
//   "env",
//   "export",
//   "unset",
//   "exit"
// };
	// int i = 0;
	// while (i < num_builtins)
	// {
	// 	if (!strcmp(string, builtins[i]))
	// 	{
	// 		printf("is a builtin\n");
	// 		//set token type to TOKEN_BUILTIN
	// 		return ;
	// 	}
	// 	i++;
	// }

int parse(t_data *data)
{
	// create_mock_token_list(data);
	scan(data);
	print_tokens(data->tokens);
	return(EXIT_SUCCESS);
}