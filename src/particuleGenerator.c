/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particuleGenerator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:26:28 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/06 12:10:11 by ecamara          ###   ########.fr       */
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
	
	step = 1;
	printf("%lf,%lf ", (double)(x + (i % (int)sqrt(num)) /** 5*/), y + (double)(i / sqrt(num)) /** 5*/);
}


int	main()
{
	int i;
	int	num = 15625;
	i = 0;
	int fd;
	fd = open("../particules", O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	while(i < num)
	{
		//sea(WIDTH, 0, HEIGH, 0);
		grid(WIDTH / 2 - 50, HEIGH / 2 - 50, i, num);
		printf("\n");
		i++;
	}
}