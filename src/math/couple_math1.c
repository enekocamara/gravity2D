/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   couple_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:45:39 by ecamara           #+#    #+#             */
/*   Updated: 2022/10/10 12:55:10 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

t_couple	c_res(t_couple c1, t_couple c2)
{
	t_couple	answer;

	answer.x = c1.x - c2.x;
	answer.y = c1.y - c2.y;
	answer.z = c1.z - c2.z;
	return (answer);
}

t_couple	c_sum(t_couple c1, t_couple c2)
{
	t_couple	answer;

	answer.x = c1.x + c2.x;
	answer.y = c1.y + c2.y;
	answer.z = c1.z + c2.z;
	return (answer);
}

t_couple	c_mul(t_couple c1, double c2)
{
	t_couple	answer;

	answer.x = c1.x * c2;
	answer.y = c1.y * c2;
	answer.z = c1.z * c2;
	return (answer);
}

t_couple	c_mul_c(t_couple vec1, t_couple vec2)
{
	t_couple	answer;

	answer.x = vec1.x * vec2.x;
	answer.y = vec1.y * vec2.y;
	answer.z = vec1.z * vec2.z;
	return (answer);
}

t_couple	c_div(t_couple vec, double n)
{
	t_couple	final;

	final.x = vec.x / n;
	final.y = vec.y / n;
	final.z = vec.z / n;
	return (final);
}
