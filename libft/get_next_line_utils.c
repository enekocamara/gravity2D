/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:03:53 by eperaita          #+#    #+#             */
/*   Updated: 2021/10/29 10:44:08 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_line_break(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_join(char *temp, char *buff)
{
	char	*new;
	int		i;

	i = 0;
	if (!temp || !buff)
		return (NULL);
	new = malloc((ft_strlen(temp) + ft_strlen(buff) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (*temp)
		new[i++] = *temp++;
	while (*buff)
		new[i++] = *buff++;
	new[i] = '\0';
	return (new);
}

char	*ft_substr_gnl(char *str, int start, size_t len)
{
	char	*new;
	int		i;

	i = 0;
	if (!str || len <= 0)
		return (NULL);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (len)
	{
		new[i++] = str[start++];
		len--;
	}
	new[i] = '\0';
	return (new);
}
