/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:03:15 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/28 14:47:10 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd( char *s, int fd)
{
	if (s == NULL)
		return (0);
	return (write(fd, s, ft_strlen(s)));
}
/*
void	ft_putnbr_fd(int n, int fd)
{
	long	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l *= -1;
	}
	if (l > 9)
		ft_putnbr_fd(l / 10, fd);
	ft_putchar_fd((l % 10) + '0', fd);
}*/

int	ft_putnbr_fd(int n, int fd)
{
	long	l;
	int		ret;

	ret = 0;
	l = n;
	if (l < 0)
	{
		ret += ft_putchar_fd('-', fd);
		l *= -1;
	}
	if (l >= 10)
		ret += ft_putnbr_fd(l / 10, fd);
	ret += ft_putchar_fd(l % 10 + '0', fd);

	return (ret);
}

