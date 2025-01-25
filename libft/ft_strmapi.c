/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:59:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 13:24:49 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	len;
	unsigned int	index;

	index = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen (s);
	res = malloc ((len + 1) * sizeof (char));
	if (!res)
		return (NULL);
	while (s[index])
	{
		res[index] = f (index, s[index]);
		index++;
	}
	res[len] = '\0';
	return (res);
}
