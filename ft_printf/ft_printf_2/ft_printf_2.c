/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:50:48 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 16:18:46 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	putchar_c(int fd, char c)
{
	return (write(fd, &c, 1));
}

static int	putstr_s(int fd, const char *s)
{
	int	n;

	if (!s)
		return (write(fd, "(null)", 6));
	n = 0;
	while (s[n])
		n += write(fd, &s[n], 1);
	return (n);
}

static int	putptr_p(int fd, void *p)
{
	size_t	v;
	int		n;

	if (!p)
		return (write(fd, "(nil)", 5));
	v = (size_t)p;
	n = 0;
	n += write(fd, "0x", 2);
	n += ft_putnbr_hex((unsigned long long)v, 0, fd);
	return (n);
}

static int	handle_conv(int fd, char c, va_list ap)
{
	if (c == 'c')
		return (putchar_c(fd, (char)va_arg(ap, int)));
	if (c == 's')
		return (putstr_s(fd, va_arg(ap, const char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_dec_signed(fd, (long long)va_arg(ap, int)));
	if (c == 'u')
		return (ft_putnbr_dec_unsigned(\
			fd, (unsigned long long)va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_hex(\
			(unsigned long long)va_arg(ap, unsigned int), 0, fd));
	if (c == 'X')
		return (ft_putnbr_hex(\
			(unsigned long long)va_arg(ap, unsigned int), 1, fd));
	if (c == 'p')
		return (putptr_p(fd, va_arg(ap, void *)));
	if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	ft_printf_fd_(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		n;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	i = 0;
	n = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			n += handle_conv(fd, fmt[i + 1], ap);
			i += 2;
		}
		else
		{
			n += write(fd, &fmt[i], 1);
			i++;
		}
	}
	va_end(ap);
	return (n);
}
