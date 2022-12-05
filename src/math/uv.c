/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:59:29 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/01 13:07:40 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

t_uv	uv(double x, double y)
{
	t_uv	temp;

	temp.x = x;
	temp.y = y;
	return (temp);
}

t_uv	uv_sum(t_uv uv1, t_uv uv2)
{
	t_uv res;

	res.x = uv1.x + uv2.x;
	res.y = uv1.y + uv2.y;
	return(res);
}

t_uv	uv_res(t_uv uv1, t_uv uv2)
{
	t_uv res;

	res.x = uv1.x - uv2.x;
	res.y = uv1.y - uv2.y;
	return(res);
}

t_uv	uv_mul(t_uv uv1, double num)
{
	t_uv res;

	res.x = uv1.x * num;
	res.y = uv1.y * num;
	return(res);
}

t_uv	uv_div(t_uv uv1, double num)
{
	t_uv res;

	res.x = uv1.x / num;
	res.y = uv1.y / num;
	return(res);
}

double	uv_len(t_uv in)
{
	return (sqrt(in.x * in.x + in.y * in.y));
}

double	uv_relativ_dis(t_uv in)
{
	return (in.x * in.x + in.y * in.y);
}

t_uv		uv_normalized(t_uv in)
{
	double	num;

	num = sqrt(in.x * in.x + in.y * in.y);
	return (uv_div(in, num));
}

t_uv	getUv(char *str)
{
	int	i;
	char *temp;
	t_uv ans;

	i = 0;
	while (str[i] != ',' && str[i] != '\0')
	{
		i++;
	}
	temp = ft_substr(str, 0, i);
	ans.x = ft_atoi_double(temp);
	ans.y = ft_atoi_double(str + i + 1);
	free(temp);
	return (ans);
}