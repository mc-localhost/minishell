
#include "../includes/minishell.h"

/*
creates mock linked list for testing
*/

void	create_mock_token_list(t_data *data)
{
    char **args = malloc(sizeof(char *) * 7);
    args[0] = strdup("-n");
    args[1] = strdup("text");
    args[2] = strdup(" ");
    args[3] = strdup("");
    args[4] = strdup(" ");
    args[5] = strdup("there are 2 spaces before me & no new line after");
    args[6] = NULL;
    t_token *token_echo = create_token(TOKEN_BUILTIN, strdup("echo"), args, NULL);
    add_token(&data->tokens, token_echo);

    // t_token *token_env = create_token(TOKEN_BUILTIN, strdup("env"), NULL, NULL);
    // add_token(&data->tokens, token_env);
}
