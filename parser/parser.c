/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:08:08 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:00 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse(t_data *data)
{
	// export _TESTING="echo $USER"
	// export _TESTING_2="$_TESTING" 
	// export _TESTING_3="ls -l | wc -l"
	// printf("%s\n", expand("$_TESTING_2", data));

	scan(data);
	printf("***		printing scanned	***\n\n");
	iterate_tokens(data, print_token);
	iterate_tokens(data, expand_token_values); // FIX!
	printf("***		printing expanded	***\n\n");
	//the problem is that after the expansion it will still be 1 token even if there are a cmd with args inside
	//export VAR="echo $USER" - won't work also
	iterate_tokens(data, print_token);
	// process_tokens(data);
	// printf("***		printing procesed final		***\n\n");
	// iterate_final_tokens(data, print_token);
	return (EXIT_SUCCESS);
}
