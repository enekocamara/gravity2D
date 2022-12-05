/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:20:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/01 17:39:39 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*whole_number(double *nb, double *neg, char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		*nb = *nb * 10 + (*str - 48);
		str++;
	}
	return (str);
}

double	ft_atod(const char *str)
{
	double	nb;
	double	neg;
	double	dec;

	neg = 1;
	dec = 10;
	nb = 0;
	if (!str)
		return (0);
	str = whole_number(&nb, &neg, (char *)str);
	if (*str == '.')
		str++;
	else
		return (nb * neg);
	while (*str >= '0' && *str <= '9')
	{
		nb += (*str - 48) / dec;
		dec *= 10;
		str++;
	}
	return (neg * nb);
}
