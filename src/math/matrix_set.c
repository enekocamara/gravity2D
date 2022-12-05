/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:36:52 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:26 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

void	set_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			matrix->matrix[j][i] = 0.0;
			i++;
		}
		j++;
	}
	matrix->matrix[0][0] = 1;
	matrix->matrix[1][1] = 1;
	matrix->matrix[2][2] = 1;
	matrix->matrix[3][3] = 1;
}

t_matrix	*set_translation(t_couple point, t_couple distance)
{
	t_matrix	*matrix;

	matrix = (t_matrix *)malloc(sizeof(*matrix));
	set_matrix(matrix);
	matrix->matrix[0][3] = distance.x + point.x;
	matrix->matrix[1][3] = distance.y + point.y;
	matrix->matrix[2][3] = distance.z + point.z;
	return (matrix);
}

void	init_m_1(t_couple vec, double last, t_matrix1 *m)
{
	m->matrix[0] = vec.x;
	m->matrix[1] = vec.y;
	m->matrix[2] = vec.z;
	m->matrix[3] = last;
}

void	asign_rotate(t_matrix *m, double sino, double coseno, t_couple p)
{
	m->matrix[0][0] = coseno + (1.0 - coseno) * (p.x * p.x);
	m->matrix[1][0] = (1 - coseno) * p.x * p.y + sino * p.z;
	m->matrix[2][0] = (1 - coseno) * p.z * p.x - sino * p.y;
	m->matrix[0][1] = (1 - coseno) * p.x * p.y - sino * p.z;
	m->matrix[1][1] = coseno + (1 - coseno) * (p.y * p.y);
	m->matrix[2][1] = (1 - coseno) * p.z * p.y + sino * p.x;
	m->matrix[0][2] = (1 - coseno) * p.x * p.z + sino * p.y;
	m->matrix[1][2] = (1 - coseno) * p.y * p.z - sino * p.x;
	m->matrix[2][2] = coseno + (1 - coseno) * (p.z * p.z);
}

t_matrix	set_rotate(double angle, t_couple old, t_couple new)
{
	t_matrix	m;
	double		coseno;
	double		sino;
	t_couple	p;
	t_couple	temp;

	set_matrix(&m);
	temp = c_mul(new, -1);
	if (new.x == old.x && new.y == old.y && new.z == old.z)
		return (m);
	else if (temp.x == old.x && temp.y == old.y && temp.z == old.z)
		p = vector(0, 1, 0);
	else
		p = normalized(cross(old, new));
	coseno = cos(angle);
	sino = sin(angle);
	asign_rotate(&m, sino, coseno, p);
	return (m);
}
