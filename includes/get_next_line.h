/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:57:22 by zmata             #+#    #+#             */
/*   Updated: 2025/09/09 18:23:24 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*gnl_strjoin(char *s1, char *s2, int *newline_position);
char	*get_next_line(int fd);
char	*read_nouveau(char *line, char *buffer, int *nl_pos, int fd);
char	*initialise_premiere_ligne(char *buffer, int *newline_position);

//-------------------------------------------------------//

void	gnl_strlcpy(char *dst, const char *src, size_t dst_size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);

//-------------------------------------------------------//

size_t	ft_strlen(const char *str);
size_t	trieur(char *buffer);

#endif