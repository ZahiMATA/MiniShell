/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:00:00 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 14:38:14 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd( char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

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
}

void	ft_print_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_putstr(tab[i++]);
}
