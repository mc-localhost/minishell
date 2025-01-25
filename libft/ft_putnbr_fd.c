/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:50 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/10 20:14:24 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd ('-', fd);
		n = -1 * n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd (n / 10, fd);
	}
	ft_putchar_fd (n % 10 + '0', fd);
}

// int	main(void)
// {
// 	ft_putnbr_fd(13425, 1);
// 	ft_putnbr_fd(0, 1);
// 	ft_putnbr_fd(-2460100, 1);
// 	return (0);
// }
