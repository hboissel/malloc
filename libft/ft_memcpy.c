/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:01:48 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/12 08:50:48 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*src_cpy;
	char			*dest_cpy;
	unsigned int	i;

	if ((!dest && !src) || (dest == src) || n == 0)
		return (dest);
	src_cpy = (char *)src;
	dest_cpy = (char *)dest;
	i = 0;
	while (i < n)
	{
		dest_cpy[i] = src_cpy[i];
		i++;
	}
	return (dest);
}
