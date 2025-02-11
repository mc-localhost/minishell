/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:08 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/11 15:27:13 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse(t_data *data)
{
	scan(data);
	printf("***		printing scanned	***\n\n");
	iterate_tokens(data, print_token);
	iterate_tokens(data, expand_token_values); //should be done separately to not expand HEREDOC - FIX!
	process_tokens(data);
	printf("***		printing procesed final		***\n\n");
	iterate_final_tokens(data, print_token);
	return (EXIT_SUCCESS);
}
