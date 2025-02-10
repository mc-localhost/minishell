
#include "../includes/minishell.h"

int	parse(t_data *data)
{
	scan(data);
	printf("***		printing scanned	***\n\n");
	iterate_tokens(data, print_token);

	iterate_tokens(data, expand_token_values);
	
	process_tokens(data);
	printf("***		printing procesed final		***\n\n");
	iterate_final_tokens(data, print_token);
	
	return (EXIT_SUCCESS);
}
