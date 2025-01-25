/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:23:16 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/12 14:46:16 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
			&& i < n - 1)
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

// int main()
// {
// 	char myStr1[] = "ABCD";
// 	char myStr2[] = "ABCD";
// 	int cmp = ft_memcmp(myStr1, myStr2, 4);

// 	if (cmp > 0) {
// 	printf("%s is greater than %s\n", myStr1, myStr2);
// 	} else if (cmp < 0) {
// 	printf("%s is greater than %s\n", myStr2, myStr1);
// 	} else {
// 	printf("%s is equal to %s\n", myStr1, myStr2);
// 	}
// }