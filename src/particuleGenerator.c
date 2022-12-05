/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particuleGenerator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:26:28 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/02 11:18:34 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

int	random_number(int max)
{
	return (rand() % max);
}

void	sea(int maxx, int minx, int maxy, int miny)
{
	double x;
	double	y;
	x = random_number(maxx + minx) - minx;
	y = random_number(maxy + miny) - miny;
	printf("%lf,%lf ", x, y);
}

void	grid(int x, int y, int i, int num)
{
	double	radious = 5;
	double	step;
	
	step = 2;
	printf("%lf,%lf ", (double)(x + (i % (int)sqrt(num)) * 5), y + (double)(i / sqrt(num)) * 5);
}


int	main()
{
	int i;
	int	num = 4000;
	i = 0;
	int fd;
	fd = open("../particules", O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	while(i < num)
	{
		//sea(WIDTH, 0, HEIGH, 0);
		grid(250, 250, i, num);
		printf("\n");
		i++;
	}
}