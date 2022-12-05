/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:12:37 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/01 17:49:18 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pass(char *str, char pass)
{
	int	i;

	i = 0;
	while (str[i] == pass)
		i++;
	return (i);
}

char	**ft_freepointer(char **p, size_t num_arrays)
{
	size_t	i;

	i = 0;
	while (i < (num_arrays + 1))
	{
		free(&p[i]);
		i++;
	}
	free(p);
	return (0);
}

char	**ft_fill(char **p, char *s, char c, size_t num_arrays)
{
	size_t	a;
	size_t	i;
	size_t	j;

	i = 0;
	a = 0;
	while (a < num_arrays && s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] != c && s[i])
			{
				j++;
				i++;
			}
			p[a] = ft_substr(s, i - j, j);
			if (!p[a])
				return (ft_freepointer(p, num_arrays));
			a++;
		}
		i++;
	}
	p[a] = NULL;
	return (p);
}

size_t	ft_num_arrays(char *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
		}
		else
		{
			while (s[i] != c && s[i])
				i++;
			n++;
		}
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	a;
	size_t	num_arrays;

	a = 0;
	if (!s)
		return (0);
	num_arrays = ft_num_arrays ((char *)s, c);
	p = (char **)malloc((num_arrays + 1) * sizeof(char *));
	if (!p)
		return (0);
	p = ft_fill(p, (char *)s, c, num_arrays);
	return (p);
}
