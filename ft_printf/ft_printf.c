/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:28:00 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/02 16:51:56 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS ft_printf(char *s, ...)
 * @RETOUR Write a library that contains ft_printf(), a function that will
 * mimic the original printf()
 * @IN t_printf "%i %i" 2 3 ; "%i %d" 0x10 0x10 ;
 * @OUT                 2 3 ;           16   16 ;
 */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static int	test_ft_printf(va_list params, t_params *p)
{
	if (p->s[p->i] && p->s[p->i] == '%' && p->s[p->i + 1] == '%')
		p->ret += ft_putchar_fd('%', p->fd);
	else if (p->s[p->i] && p->s[p->i] == '%' && p->s[p->i + 1] == 'c')
		p->ret += ft_putchar_fd(va_arg(params, int), p->fd);
	else if (p->s[p->i] && p->s[p->i] == '%' && p->s[p->i + 1] == 's')
		p->ret += ft_putstr_fd(va_arg(params, char *), p->fd);
	else if (p->s[p->i] && p->s[p->i] == '%' && (p->s[p->i + 1] == 'd' || p->s[p->i + 1] == 'i'))
		p->ret += ft_putnbr_fd(va_arg(params, int), p->fd);
	/*
	else if (s[i] && s[i] == '%' && s[i + 1] == 'u')
		*ret += print_string_u(va_arg(params, unsigned int));
	else if (s[i] && s[i] == '%' && s[i + 1] == 'x')
		*ret += print_string_hex
			(va_arg(params, unsigned int), "0123456789abcdef", 16);
	else if (s[i] && s[i] == '%' && s[i + 1] == 'X')
		*ret += print_string_hex
			(va_arg(params, unsigned int), "0123456789ABCDEF", 16);
	else if (s[i] && s[i] == '%' && s[i + 1] == 'p')
		*ret += print_string_p(va_arg(params, unsigned long));*/
	else
		p->ret += ft_putchar_fd(p->s[p->i--], p->fd);
	return (p->i += 2);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	t_params	p;
	va_list		params;

	ft_bzero(&p, sizeof(t_params));
	p.s = (char *)s;
	p.fd = fd;
	if (s == NULL)
		return (-1);
	va_start(params, s);
	while (p.s[p.i])
		test_ft_printf(params, &p);
	va_end(params);
	return (p.ret);
}

/*
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int	_printf_(const char *s, ...)
{

	int	n;
	va_list argv;
	va_start(argv, s);
	n = vprintf(s, argv);
	va_end(argv);
	//printf("\n");
	return (n);

}

void test0()
{
        char *s = "%u %s\n";
        int n = _printf_(s, NULL, NULL);
        printf("printf.n=%d\n", n);
        n = ft_printf(s, NULL, NULL);
        printf("FTprintf.n=%d\n", n);

        s = "%%%%%X %i %x %u %x %p %p %p %p %% %c\n";
        n = _printf_(s, 255, 255, -1, -1, 4294967296, s, -1, 0, \
	0x800000000000000, 65);
        printf("printf.n=%d\n", n);
        n = ft_printf(s, 255, 255, -1, -1, 4294967296, s, -1, 0, \
	0x800000000000000, 67);
        printf("FTprintf.n=%d\n", n);

	s = NULL;
	n = _printf_(0, NULL, NULL);
        printf("printf.n=%d\n", n);
        n = ft_printf(0, NULL, NULL);
	printf("FTprintf.n=%d\n", n);
}

void test(char *s1, char *s2, char *s3)
{

	//int n = _printf_(s1, s2, strtol(s3, NULL, 0));
	int n = _printf_(s1, s2, s3);
	printf("printf.n=%d\n", n);

        n = ft_printf(s1, s2, s3);
        //printf("ftprintf:n=%d\n", n);
	//printf("print_s.n=%d\n", print_string("12345"));

}

int	main(int argc, char ** argv)
{
	//printf("str_len=%zu\n", ft_strlen("124356"));
	if (argc == 1) test0();
	else if(argc > 1) test(argv[1], argv[2], argv[3]);
	else ft_printf("Wrong args\n");
}
*/
