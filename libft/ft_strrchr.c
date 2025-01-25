/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:23:16 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/13 12:48:55 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen (str);
	while (len >= 0)
	{
		if (*(unsigned char *)(str + len) == (unsigned char)c)
			return ((char *)(str + len));
		len--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char string1[] = "needle (needle)";
// 	int chr1 = 'n';
// 	printf("%s", ft_strrchr(string1, chr1));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strrchr(string1, chr1));
// 	printf("%s","\n");
// 	const char string2[] = "Find the end";
// 	int chr2 = '\0';
// 	printf("%s", ft_strrchr(string2, chr2));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strrchr(string2, chr2));
// 	printf("%s","\n");
// 	const char string3[] = "No such char";
// 	int chr3 = '!';
// 	printf("%s", ft_strrchr(string3, chr3));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strrchr(string3, chr3));
// 	return (0);
// }