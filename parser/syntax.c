/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:38:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 14:01:37 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
DON'T FORGET TO WRITE TO STDERR, NOT STDOUT

1) unclosed quotes. bash supports it by asking for more input
until quote is met, but we don't have to handle that.

echo I don't care
bash: syntax error: '" unexpected EOF while looking for matching '"

echo "Hello
bash: syntax error: '"' unexpected EOF while looking for matching '"
*/

/*
2) first token is TOKEN_PIPE and not a command

bash-3.2$ | echo Hello
bash: syntax error near unexpected token `|'
*/

/*
3) consecutive pipes or redirections

bash-3.2$ <<<<<<<< EOF echo
bash: syntax error near unexpected token `<<<'
*/