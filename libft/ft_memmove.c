/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:01:38 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/14 08:39:05 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_cpy;
	char	*src_cpy;
	int		i;

	if (!n)
		return (dest);
	else if (!dest && !src)
		return (NULL);
	i = -1;
	src_cpy = (char *)src;
	dest_cpy = (char *)dest;
	if (src_cpy > dest_cpy)
	{
		while (++i < (int)n)
			dest_cpy[i] = src_cpy[i];
	}
	else
	{
		i = n;
		while (--i >= 0)
			dest_cpy[i] = src_cpy[i];
	}
	return (dest);
}
