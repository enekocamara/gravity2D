/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:12:37 by eperaita          #+#    #+#             */
/*   Updated: 2022/08/30 18:18:56 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freepointer_str(char **p, size_t num_arrays)
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

char	**ft_fill_str(char **p, char *s, char *str, size_t num_arrays)
{
	size_t	a;
	size_t	i;
	size_t	j;

	i = 0;
	a = 0;
	while (a < num_arrays && s[i])
	{
		if (!ft_c_str_cmp(s[i], str))
		{
			j = 0;
			while (!ft_c_str_cmp(s[i], str) && s[i])
			{
				j++;
				i++;
			}
			p[a] = ft_substr(s, i - j, j);
			if (!p[a])
				return (ft_freepointer_str(p, num_arrays));
			a++;
		}
		i++;
	}
	p[a] = NULL;
	return (p);
}

size_t	ft_num_arrays_str(char *s, char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (ft_c_str_cmp(s[i], str))
		{
			while (ft_c_str_cmp(s[i], str) && s[i])
				i++;
		}
		else
		{
			while (!ft_c_str_cmp(s[i], str) && s[i])
				i++;
			n++;
		}
	}
	return (n);
}

char	**ft_split_str(char const *s, char *str)
{
	char	**p;
	size_t	a;
	size_t	num_arrays;

	a = 0;
	if (!s)
		return (0);
	num_arrays = ft_num_arrays_str((char *)s, str);
	p = (char **)malloc((num_arrays + 1) * sizeof(char *));
	if (!p)
		return (0);
	p = ft_fill_str(p, (char *)s, str, num_arrays);
	return (p);
}
