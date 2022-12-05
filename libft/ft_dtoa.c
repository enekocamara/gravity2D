/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:08:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/01 17:53:35 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int	str_size(double value, int *dot)
{
	int	len;
	int	value_int;

	len = 0;
	value_int = (int)value;
	if (value - value_int != 0)
		*dot = 1;
	if (value < 0)
	{
		len++;
		value *= -1;
	}
	value -= value_int;
	while (value_int)
	{
		value_int /= 10;
		len++;
	}
	while (value > 0.00001)
	{
		value *= 10;
		value -= (int)value;
		len++;
	}
	return (len);
}

int	len_int(int n)
{
	int	len;

	len = 0;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_dtoa2(double value, char *str, int dot, int i)
{
	int	len;
	int	value_int;

	value_int = (int)value;
	value -= value_int;
	len = len_int(value_int);
	while (value_int)
	{
		str[i++] = value_int / pow(10, len - 1) + '0';
		value_int %= (int)pow(10, len - 1);
		len--;
	}
	if (dot)
		str[i++] = '.';
	while (value > 0.0001)
	{
		value *= 10;
		str[i++] = ((int)value) + '0';
		value -= (int)value;
	}
	return (str);
}

char	*ft_dtoa(double value)
{
	int		dot;
	int		len;
	char	*str;
	int		i;

	dot = 0;
	i = 0;
	len = str_size(value, &dot);
	str = (char *)malloc(len + 1 + dot);
	str[len + dot] = '\0';
	if (value < 0)
		str[i++] = '-';
	return (ft_dtoa2(value, str, dot, i));
}
