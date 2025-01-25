/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:36:31 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/12 13:45:07 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cnt_digits(int n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		digits++;
		n *= -1;
	}
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			digits;

	digits = ft_cnt_digits (n);
	s = malloc ((digits + 1) * sizeof (char));
	if (!s)
		return (NULL);
	s[digits] = '\0';
	if (n == -2147483648)
		ft_strlcpy (s, "-2147483648", 12);
	if (n == 0)
		s[0] = '0';
	if (n < 0 && n != -2147483648)
	{
		s[0] = '-';
		n *= -1;
	}
	digits--;
	while (n > 0)
	{
		s[digits] = (n % 10) + '0';
		n /= 10;
		digits--;
	}
	return (s);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa (-236));
// 	printf("%s\n", ft_itoa (6));
// 	printf("%s\n", ft_itoa (0));
// 	return (0);
// }
