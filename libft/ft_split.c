/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:30:20 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/16 12:03:55 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count_word(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && (*s != c))
			s++;
	}
	return (count);
}

static char	*ft_get_word(char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static void	*ft_free_alloc(char **strs, int pos)
{
	int	i;

	i = 0;
	while (i <= pos)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static int	ft_move(char *s, char c, int i, int how)
{
	if (!how)
	{
		while (s[i] && s[i] == c)
			i++;
	}
	else
	{
		while (s[i] && s[i] != c)
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i_w;
	int		i;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_count_word((char *)s, c) + 1));
	if (!strs)
		return (NULL);
	i_w = 0;
	i = 0;
	while (s[i])
	{
		i = ft_move((char *)s, c, i, 0);
		if (s[i])
		{
			strs[i_w] = ft_get_word((char *)s + i, c);
			if (!strs[i_w++])
				return (ft_free_alloc(strs, --i_w));
			i = ft_move((char *)s, c, i, 1);
		}
	}
	strs[i_w] = 0;
	return (strs);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**res;

	(void)argc;
	res = ft_split(argv[1], argv[2][0]);
	while (*res)
	{
		printf("%s-\n", *res);
		res++;
	}
	return (0);
}*/
