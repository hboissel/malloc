/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 04:55:03 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/12 09:00:18 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*s_cpy;
	unsigned int	i;

	s_cpy = s;
	i = 0;
	while (i < n)
	{
		s_cpy[i] = (char)c;
		i++;
	}
	return (s);
}
