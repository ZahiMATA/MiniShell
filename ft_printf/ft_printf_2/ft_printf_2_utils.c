/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:03:53 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 16:16:23 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putnbr_dec_signed(int fd, long long v)
{
	char	buf[21];
	int		i;
	int		n;
	int		neg;

	if (v == 0)
		return (write(fd, "0", 1));
	neg = (v < 0);
	if (neg)
		v = -v;
	i = 20;
	buf[i] = '\0';
	while (v > 0 && i > 0)
	{
		buf[--i] = '0' + (v % 10);
		v /= 10;
	}
	if (neg)
		buf[--i] = '-';
	n = 0;
	while (buf[i])
		n += write(fd, &buf[i++], 1);
	return (n);
}

int	ft_putnbr_dec_unsigned(int fd, unsigned long long v)
{
	char	buf[21];
	int		i;
	int		n;

	if (v == 0)
		return (write(fd, "0", 1));
	i = 20;
	buf[i] = '\0';
	while (v > 0 && i > 0)
	{
		buf[--i] = '0' + (v % 10);
		v /= 10;
	}
	n = 0;
	while (buf[i])
		n += write(fd, &buf[i++], 1);
	return (n);
}

int	ft_putnbr_hex(unsigned long long v, int upper, int fd)
{
	const char	*base;
	char		buf[17];
	int			i;
	int			n;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (v == 0)
		return (write(fd, "0", 1));
	i = 16;
	buf[i] = '\0';
	while (v && i > 0)
	{
		buf[--i] = base[v & 0xF];
		v >>= 4;
	}
	n = 0;
	while (buf[i])
		n += write(fd, &buf[i++], 1);
	return (n);
}
