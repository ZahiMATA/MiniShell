/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:57:22 by zmata             #+#    #+#             */
/*   Updated: 2025/09/09 18:21:10 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"


char	*gnl_strjoin(char *s1, char *s2, int *newline_position)
{
	char	*combined_string;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	combined_string = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!combined_string)
		return (free(s1), NULL);
	ft_memcpy(combined_string, s1, s1_len);
	free(s1);
	ft_memcpy(combined_string + s1_len, s2, s2_len + 1);
	if (s1_len + s2_len > 0 && *(combined_string + s1_len + s2_len - 1) == '\n')
		*newline_position = 0;
	return (combined_string);
}

void	gnl_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;

	i = 0;
	if (dst_size > 0)
	{
		while (src[i] && i < dst_size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}
