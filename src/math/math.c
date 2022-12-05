/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:28:43 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:20 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

double	power(double x)
{
	return (x * x);
}

double	clamp(double min, double max, double value)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	ft_abs(double num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

double	get_angle(t_couple vec1, t_couple vec2)
{
	return (acos(dot(vec1, vec2)));
}

double	ft_to_sec(struct timeval time)
{
	return (time.tv_sec + time.tv_usec / 1000000.0);
}
