/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:38 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/14 15:25:11 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
These are helper functions for looping through
tokens and final tokens. The most obvious use case is printing out
the tokens.
*/

void	iterate_tokens(t_data *data, token_func func)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		func(current, data);
		current = current->next;
	}
}

void	iterate_final_tokens(t_data *data, token_func func)
{
	t_token	*current;

	current = data->final_tokens;
	while (current)
	{
		func(current, data);
		current = current->next;
	}
}

void	print_token(t_token *token, t_data *data) //rewrite to pass norm
{
	int				i;
	t_redirection	*redir;

	(void)data;
	if (token->type == PROCESSED)
		return ;
	printf("Type: %d, Value: %s\n", token->type, token->value);
	i = 0;
	while (i < token->args_count)
	{
		printf("%i arg: %s\n", i, token->args[i]);
		i++;
	}
	if (token->redirections_in)
	{
		printf("redirections in\n");
		redir = token->redirections_in;
		while (redir)
		{
			printf("type %d: %s\n", redir->type, redir->file);
			redir = redir->next;
		}
	}
	if (token->redirections_out)
	{
		printf("redirections out\n");
		redir = token->redirections_out;
		while (redir)
		{
			printf("type %d: %s\n", redir->type, redir->file);
			redir = redir->next;
		}
	}
}

// void	expand_token_values(t_token *token, t_data *data) //WRONG
// {
// 	if (token->type != TOKEN_STRING && token->type != TOKEN_STRING_DOUBLEQ)
// 		return ;
// 	token->value = expand(token->value, data);
// }
