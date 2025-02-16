/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 18:36:37 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*

1) Unclosed quotes. Bash supports it by asking for more input
until the closing quote is met, but we don't have to handle that.

echo I don't care
bash: syntax error: '" unexpected EOF while looking for matching '"

echo "Hello
bash: syntax error: '"' unexpected EOF while looking for matching '"

2) The first token is TOKEN_PIPE and not a command.

bash-3.2$ | echo Hello
bash: syntax error near unexpected token `|'

3) Consecutive pipes or redirections or a pipe after redirection.

bash-3.2$ <<<<<<<< EOF echo
bash: syntax error near unexpected token `<<<'

bash-3.2$ echo | |
bash: syntax error near unexpected token `|'

bash-3.2$ <<| echo wtf
bash: syntax error near unexpected token `|'

4) Nothing after redirection. In our case also after a pipe.

bash-3.2$ <<
bash: syntax error near unexpected token `newline'

*/

void	print_syntax_error(t_token *token)
{
	ft_putstr_stderr("minishell: syntax error near unexpected token `");
	if (token && token->value)
	{
		ft_putstr_stderr(token->value);
		ft_putstr_stderr("'\n");
	}
	else
		ft_putstr_stderr("newline'\n");
	exit(258); // execution should deal with this
}

void	unclosed_quotes_error(char q_type)
{
	ft_putstr_stderr("minishell: syntax error: \
	unexpected EOF while looking for matching '");
	ft_putchar_stderr(q_type);
	ft_putstr_stderr("'\n");
	exit(258); // execution should deal with this
}

/*
one case left
cat <file |>file
- no command after pipe but should still work (it won't throw error)
*/