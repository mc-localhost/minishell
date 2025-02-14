/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:08 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/14 23:17:45 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Merging tokens is needed so that if, for example, echo command is written like
'e'"cho" 
it will stil work and not try to execute 'e'.
*/

static void	merge_tokens(t_token **head)
		// for now a random type of STRING token type stays
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
		current->value = ft_strjoin(current->value, current->next->value);
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
	// export _TESTING="echo $USER"
	// export _TESTING_2="$_TESTING"
	// export _TESTING_3="ls -l | wc -l"
	// printf("%s\n", expand("$_TESTING_2", data));
	scan(data);
	printf("***		printing scanned	***\n\n");
	iterate_tokens(data, print_token);
	iterate_tokens(data, expand_token_values);
	printf("***		printing expanded	***\n\n");
	iterate_tokens(data, print_token);
	merge_tokens(&data->tokens);
	printf("***		printing merged	***\n\n");
	iterate_tokens(data, print_token);
	// here we might as well just remove spaces and processed tokens first
	process_tokens(data);
	printf("***		printing procesed final		***\n\n");
	iterate_final_tokens(data, print_token);
	return (EXIT_SUCCESS);
}
