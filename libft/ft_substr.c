/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:04:10 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/14 07:49:27 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	else if ((ft_strlen(s) - start) < len)
		new_str = malloc(ft_strlen(s) - start + 1);
	else
		new_str = malloc(len + 1);
	if (new_str == NULL)
		return (new_str);
	i = 0;
	if (start < ft_strlen(s) && s)
	{
		while (s[start + i] && i < len)
		{
			new_str[i] = s[start + i];
			i++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}
