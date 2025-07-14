/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:44:09 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 12:41:16 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		c = nb + '0';
		write(fd, &c, 1);
	}
}
/*
int main(void)
{
    int num1 = 12345;
    int num2 = -2147483648;

    // Output positive integer num1 to standard output (file descriptor 1)
    ft_putnbr_fd(num1, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);

    // Output negative integer num2 to standard output (file descriptor 1)
    ft_putnbr_fd(num2, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}*/
