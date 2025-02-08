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
	int		i;

	new_token = safe_malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("malloc failed for token creation\n");
		free_all();
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->args_count = 0;
	if (args)
	{
		new_token->args = args;
		i = 0;
		while (args[i])
			i++;
		new_token->args_count = i;
	}
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

void	print_token(t_token *token, t_data *data)
{
	int	i;

	(void)data; // Unused parameter
	printf("Type: %d, Value: %s, File: %s\n", token->type, token->value,
		token->file);
	i = 0;
	while (i < token->args_count)
	{
		printf("%i arg: %s\n", i, token->args[i]);
		i++;
	}
}
