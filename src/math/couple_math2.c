/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   couple_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:50 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/01 13:15:02 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

double	len2(t_couple vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

double	len(t_couple vec)
{
	return (sqrt(len2(vec)));
}
/*
t_couple	get_point(t_intersect intersect, int boo)
{
	t_couple	point;
	double		index;

	index = 0.0001;
	point = c_sum(c_mul(intersect.ray.direction, intersect.t),
			intersect.ray.origin);
	if (boo)
		return (c_sum(c_mul(intersect.normal, index), point));
	return (point);
}
*/
t_couple	set_point(t_couple origin, t_couple direction, double t)
{
	return (c_sum(c_mul(direction, t), origin));
}

t_couple	c_clamp(double min, double max, t_couple value)
{
	value.x = clamp(min, max, value.x);
	value.y = clamp(min, max, value.y);
	value.z = clamp(min, max, value.z);
	return (value);
}
