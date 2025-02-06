
#include "../includes/minishell.h"

// void pwd() {
// 	char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         printf("%s\n", cwd);
//     } else {
//         perror("getcwd() error");
//     }
// }

void pwd(t_data *data)
{
	char	*cwd;

	cwd = find_env_var(&data->envs, "PWD");
	if (!cwd)
		perror("pwd error"); //to replace with better error handling
    else
		printf("%s\n", cwd);
}
