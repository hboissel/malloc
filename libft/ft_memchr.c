/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:11:25 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/12 10:12:40 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s_cpy;
	unsigned char	c_cpy;

	s_cpy = (unsigned char *)s;
	c_cpy = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s_cpy[i] == c_cpy)
			return (s_cpy + i);
		i++;
	}
	return (NULL);
}
