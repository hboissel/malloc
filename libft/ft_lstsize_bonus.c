/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:58:12 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/14 11:02:53 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;

	if (lst)
	{
		size = 1;
		while (lst->next)
		{
			size++;
			lst = lst->next;
		}
	}
	else
		size = 0;
	return (size);
}
