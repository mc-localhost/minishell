/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:38:13 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 16:11:58 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value, char **args, char *file)
{
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("malloc failed for token creation\n");
		free_all();
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->args = args;
	new_token->file = file;
	new_token->prev = NULL;
	new_token->next = NULL;
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

void	print_tokens(t_token *current)
{
	while (current)
	{
		printf("Type: %d, Value: %s, File: %s\n", current->type, current->value,
			current->file);
		current = current->next;
	}
}
