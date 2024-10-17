/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:03:39 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/10 12:18:45 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	ln_dest;
	unsigned int	i_src;

	ln_dest = 0;
	while (ln_dest < size && *dst)
	{
		dst++;
		ln_dest++;
	}
	if (ln_dest == size)
		return (ln_dest + ft_strlen(src));
	i_src = 0;
	while (src[i_src])
	{
		if (i_src < (size - ln_dest - 1))
			*dst++ = src[i_src];
		i_src++;
	}
	*dst = '\0';
	return (ln_dest + i_src);
}
