/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:33:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 16:13:59 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_params
{
	char	*s;
	int		i;
	int		ret;
	int		fd;
}	t_params;

int	ft_printf_fd(int fd, const char *s, ...);
int	ft_putnbr_dec_signed(int fd, long long v);
int	ft_putnbr_dec_unsigned(int fd, unsigned long long v);
int	ft_putnbr_hex(unsigned long long v, int upper, int fd);

#endif