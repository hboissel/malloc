/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:43:30 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/16 12:03:31 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_ctrl(char *s2, char *s1, unsigned int ln)
{
	if (!*s2)
		return ((char *)s1);
	if (!ln)
		return (NULL);
	return (NULL);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	ln;

	ln = (unsigned int)len;
	i = 0;
	j = 0;
	if (!*s2 || !ln)
		return (ft_ctrl((char *)s2, (char *)s1, ln));
	while (s1[i] && i < ln)
	{
		if (!s2[j])
			return ((char *)s1 + i - j);
		else if (s2[j] == s1[i])
			j++;
		else if (j)
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	if (!s2[j])
		return ((char *)s1 + i - j);
	return (NULL);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
	return (0);
}*/
