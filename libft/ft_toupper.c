/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/12 13:50:17 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
		return (i -= 32);
	return (i);
}

// int main(void)
// {
// 	char	src = 'e';

// 	printf ("%d", ft_toupper (src));
// 	printf ("%s", "\n");
// 	printf ("%d", toupper (src));
// 	return (0);
// }