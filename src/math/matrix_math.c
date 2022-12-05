/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:37:39 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:22 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

t_matrix	*matrix_mul(t_matrix *m1, t_matrix *m2)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*m_res;

	m_res = (t_matrix *)malloc(sizeof(*m_res));
	set_matrix(m_res);
	k = 0;
	while (k < 4)
	{
		j = 0;
		while (j < 4)
		{
			i = 0;
			while (i < 4)
			{
				m_res->matrix[k][j] += m1->matrix[k][i] * m2->matrix[i][j];
				i++;
			}
			j++;
		}
		k++;
	}
	return (m_res);
}

t_couple	rotate(t_couple vec, t_matrix *matrix)
{
	t_couple	result;

	result.x = vec.x * matrix->matrix[0][0] + vec.y
		* matrix->matrix[0][1] + vec.z * matrix->matrix[0][2];
	result.y = vec.x * matrix->matrix[1][0] + vec.y
		* matrix->matrix[1][1] + vec.z * matrix->matrix[1][2];
	result.z = vec.x * matrix->matrix[2][0] + vec.y
		* matrix->matrix[2][1] + vec.z * matrix->matrix[2][2];
	return (result);
}

t_ray	trans_ray(t_ray *ray, t_matrix *trans, t_matrix *rot)
{
	t_ray	new;

	new.direction = copy_couple(ray->direction);
	new.origin = copy_couple(ray->origin);
	if (trans != NULL)
		new.origin = translate(new.origin, trans);
	if (rot != NULL)
	{
		new.direction = rotate(new.direction, rot);
		new.origin = rotate(new.origin, rot);
	}
	return (new);
}

t_couple	translate(t_couple vec, t_matrix *matrix)
{
	t_couple	new;

	new.x = matrix->matrix[0][3] + vec.x;
	new.y = matrix->matrix[1][3] + vec.y;
	new.z = matrix->matrix[2][3] + vec.z;
	return (new);
}

t_couple	antitranslate(t_couple vec, t_matrix *matrix)
{
	t_couple	new;

	new.x = -matrix->matrix[0][3] + vec.x;
	new.y = -matrix->matrix[1][3] + vec.y;
	new.z = -matrix->matrix[2][3] + vec.z;
	return (new);
}
