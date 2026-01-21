/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:29:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 19:30:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOC ft_strchr
 * @RETOUR La fonction strchr() renvoie un pointeur sur la première occurrence
 * du caractère c de la chaîne s
 * La fonction renvoit un pointeur sur le caractère correspondant ou NULL si le
 * caractère  n'est pas trouvé.  L'octet nul de terminaison est considéré comme
 * faisant partie de la chaîne, de sorte que si c est spécifié comme '\0',
 * cette fonction renvoit un pointeur sur le terminateur.
 * @IN ft_strchr "Hello world" r
 * @OUT rld
 */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
#include <stdio.h>
void	test1()
{
	char	*s1;
	char	*s2;

	s1 = "Hello world";
	s2 = ft_strchr(s1, 'r');
	printf("%p:%s\n%p:%s", s1, s1, s2, s2);
}

void	test2(char *s, char c)
{
	char	*s1;

	s1 = ft_strchr(s, c);
	printf("IN =%p:%s\n", &s, s);
	printf("OUT=%p:%s\n", &s1, s1);
}

int	main (int argc, char *argv[])
{
	if(argc == 1) test1();
	if(argc == 2) test2(argv[1], '\0');
	if(argc == 3) test2(argv[1], argv[2][0]);
}*/
