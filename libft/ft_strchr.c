/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:23:16 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/13 12:47:38 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen (str);
	while (i <= len)
	{
		if (*(unsigned char *)(str + i) == (unsigned char)c)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char string1[] = "needle (needle)";
// 	int chr1 = 'n';
// 	printf("%s", ft_strchr(string1, chr1));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strchr(string1, chr1));
// 	printf("%s","\n");
// 	const char string2[] = "Find the end";
// 	int chr2 = '\0';
// 	printf("%s", ft_strchr(string2, chr2));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strchr(string2, chr2));
// 	printf("%s","\n");
// 	const char string3[] = "No such char";
// 	int chr3 = '!';
// 	printf("%s", ft_strchr(string3, chr3));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strchr(string3, chr3));
// 	return (0);
// }