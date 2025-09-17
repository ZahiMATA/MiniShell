/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:20:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 14:09:59 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	next_overflows(unsigned long long cut,
	unsigned long long acc, unsigned int dig)
{
	if (acc > cut / 10ULL)
		return (1);
	if (acc == cut / 10ULL && dig > (cut % 10ULL))
		return (1);
	return (0);
}

static void	init_parse(const char *s, size_t *i, int *sign,
	unsigned long long *acc)
{
	*i = 0;
	*sign = 1;
	*acc = 0;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static unsigned long long	cut_for_sign(int sign)
{
	if (sign == 1)
		return ((unsigned long long)LLONG_MAX);
	return ((unsigned long long)LLONG_MAX + 1ULL);
}

static int	accumulate_digits(const char *s, size_t *i,
	unsigned long long *acc, unsigned long long cut)
{
	unsigned int	dig;

	while (s[*i])
	{
		dig = (unsigned int)(s[*i] - '0');
		if (next_overflows(cut, *acc, dig))
			return (1);
		*acc = (*acc * 10ULL) + dig;
		(*i)++;
	}
	return (0);
}

int	atoll_overflow(const char *s, long long *out)
{
	size_t				i;
	int					sign;
	unsigned long long	acc;
	unsigned long long	cut;

	init_parse(s, &i, &sign, &acc);
	cut = cut_for_sign(sign);
	if (accumulate_digits(s, &i, &acc, cut))
		return (1);
	if (out)
	{
		if (sign == 1)
			*out = (long long)acc;
		else
			*out = -(long long)acc;
	}
	return (0);
}
