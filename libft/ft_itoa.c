/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:51:00 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/14 08:21:12 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_get_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			size;
	long int	nb;

	nb = (long int)n;
	size = ft_get_size(nb);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	else if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[--size] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}
