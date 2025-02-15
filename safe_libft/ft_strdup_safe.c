/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:08:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:32:02 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_safe(const char *src)
{
	char	*dest;
	int		len;

	len = ft_strlen (src);
	dest = safe_malloc ((sizeof (char)) * (len + 1));
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
