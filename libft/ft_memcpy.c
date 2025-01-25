/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:31:23 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 13:33:59 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*udst;
	const char	*usrc;

	if (!dst && !src)
		return (dst);
	udst = dst;
	usrc = src;
	while (n > 0)
	{
		*udst = *usrc;
		udst++;
		usrc++;
		n--;
	}
	return (dst);
}

// int main() 
// { 
// 	char csrc[] = "GeeksforGeeks"; 
// 	char cdest[100]; 
// 	ft_memcpy(cdest, csrc, strlen(csrc)+1); 
// 	printf("Copied string is %s", cdest); 
// }