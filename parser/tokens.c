/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:38:13 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:34:16 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	if (!token)
	{
		printf("malloc failed for token creation\n");
		exit(EXIT_FAILURE);
	}
	token->value = NULL;
	token->args = NULL;
	token->args_count = 0;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

/*
Used by scanner to push all possible tokens into data.tokens linked list.
Later this list will get compressed into data.final_tokens
by final_tokens.c functions.
*/

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = init_token();
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}
