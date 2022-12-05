/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   couple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:58:06 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:17 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

t_couple	point(double x, double y, double z)
{
	t_couple	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_couple	vector(double x, double y, double z)
{
	t_couple	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_couple	copy_couple(t_couple original)
{
	t_couple	copy;

	copy.x = original.x;
	copy.y = original.y;
	copy.z = original.z;
	return (copy);
}

t_couple	get_couple(char *str)
{
	char		**hold;
	t_couple	vec;

	hold = ft_split(str, ',');
	if (!hold || ft_strlen2d((const char **)hold) != 3)
		return (vector(0, 0, 0));
	vec.x = ft_atoi_double(hold[0]);
	vec.y = ft_atoi_double(hold[1]);
	vec.z = ft_atoi_double(hold[2]);
	return (vec);
}

t_ray	set_ray(t_couple origin, t_couple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
