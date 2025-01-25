/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:31:23 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/10 19:03:38 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*us;

	us = s;
	while (n > 0)
	{
		*us = '\0';
		us++;
		n--;
	}
}

// int main() 
// { 
//     char str[50] = "GeeksForGeeks is for programming geeks."; 
//     printf("\nBefore memset(): %s\n", str); 
//     // Fill 8 characters starting from str[13] with '.' 
//     ft_bzero(str + 13, 8*sizeof(char)); 
//     printf("After memset():  %s", str); 
//     return 0; 
// } 