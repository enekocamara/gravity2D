/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   couple_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:47:24 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:15 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

double	dot(t_couple vec1, t_couple vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_couple	cross(t_couple vec1, t_couple vec2)
{
	t_couple	final;

	final.x = vec1.y * vec2.z - vec1.z * vec2.y;
	final.y = vec1.z * vec2.x - vec1.x * vec2.z;
	final.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (final);
}

t_couple	normalized(t_couple vec)
{
	t_couple	final;
	double		lenght;

	lenght = len(vec);
	final = c_div(vec, lenght);
	return (final);
}

void	normalize(t_couple *vec)
{
	double	lenght;

	lenght = len(*vec);
	*vec = c_div(*vec, lenght);
}
