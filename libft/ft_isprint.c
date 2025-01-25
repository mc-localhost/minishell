/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/10 18:41:12 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	src = ' ';

// 	printf ("%d", ft_isprint (src));
// 	printf ("%s", "\n");
// 	printf ("%d", isprint (src));
// 	return (0);
// }