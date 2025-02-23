/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:08 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/23 12:03:12 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	unlink_processed(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	current = *head;
	while (current)
	{
		if (current->type != PROCESSED)
		{
			current = current->next;
			continue ;
		}
		temp = current->next;
		if (current->prev)
			current->prev->next = current->next;
		else
			*head = current->next;
		if (current->next)
			current->next->prev = current->prev;
		current = temp;
	}
}

static void	unlink_pipes(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	current = *head;
	while (current)
	{
		if (current->type != TOKEN_PIPE)
		{
			current = current->next;
			continue ;
		}
		temp = current->next;
		if (current->prev)
			current->prev->next = current->next;
		else
			*head = current->next;
		if (current->next)
			current->next->prev = current->prev;
		current = temp;
	}
}

/*
Merging tokens is needed so that if, for example, echo command is written like
'e'"cho"
it will stil work and not try to execute 'e'.

When merging, only 1 token of type TOKEN_STRING_SINGLQ remains
with a value equal to everything joined before next TOKEN_SPACE.
*/

static void	merge_tokens(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current && current->next)
	{
		if (!is_string(current->type) || !is_string(current->next->type))
		{
			current = current->next;
			continue ;
		}
		current->value = ft_strjoin_safe(current->value, current->next->value);
		current->type = TOKEN_STRING_SINGLQ;
		if (current->next->next == NULL)
		{
			current->next = NULL;
			return ;
		}
		current->next->next->prev = current;
		current->next = current->next->next;
	}
}

int	parse(t_data *data)
{
	if (scan(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("***		printing scanned	***\n\n");
	// iterate_tokens(data, print_token);

	if (first_is_pipe(&data->tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	iterate_tokens(data, expand_token_values);
	// printf("***		printing expanded	***\n\n");
	// iterate_tokens(data, print_token);

	unlink_processed(&data->tokens);
	// printf("***		printing after PROCESSED removal	***\n\n");
	// iterate_tokens(data, print_token);

	merge_tokens(&data->tokens);
	// printf("***		printing merged	***\n\n");
	// iterate_tokens(data, print_token);

	if (process_tokens(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (last_is_pipe(&data->final_tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	unlink_pipes(&data->final_tokens);

	// printf("number of pipes: %d\n", data->num_pipes);
	// printf("***		printing procesed final		***\n\n");
	// iterate_final_tokens(data, print_token);

	return (EXIT_SUCCESS);
}
