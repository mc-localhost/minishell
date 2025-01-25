/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:08:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/15 11:58:36 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		len;

	len = ft_strlen (src);
	dest = malloc ((sizeof (char)) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	len--;
	while (len >= 0)
	{
		dest[len] = src[len];
		len--;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = "String";
// 	s2 = ft_strdup (s1);
// 	printf ("%s\n", s2);
// 	free (s2);
// }
