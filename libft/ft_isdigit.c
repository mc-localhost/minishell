/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/10 18:41:06 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	src = 'H';

// 	printf ("%d", ft_isdigit (src));
// 	printf ("%s", "\n");
// 	printf ("%d", isdigit (src));
// 	return (0);
// }