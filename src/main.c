/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:40:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/12/06 13:26:02 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	set_map(t_data *data)
{
	data->map.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGH);
	data->map.add = (int *)mlx_get_data_addr(data->map.img,
			&data->map.bpp, &data->map.w,
			&data->map.endian);
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGH, "SIM");
}

int	random_number(int max)
{
	return (rand() % max);
}

void	printf_uv(t_uv uv)
{
	printf("[%lf][%lf]\n", uv.x, uv.y);
}

void	render(t_data *data)
{
	int	i;

	i = 0;
	g_ids = 0;
	cubism(data);
	while (i < THREADS)
	{
		if (pthread_create(&data->mutex[i], NULL, &gravity,
				data) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(data->mutex[i], NULL);
	destroyTree(data->tree);
}

void	*clearMultiScreen(void *temp)
{
	int	i;
	int	j;
	int	temp_id;

	temp_id = g_ids;
	g_ids++;
	t_data *data = temp;
	j = temp_id;
	while(j < HEIGH)
	{
		i = 0;
		while (i < WIDTH)
		{
			data->bakery.frames->add[j * WIDTH + i] = 0;
			i++;
		}
		j += THREADS;
	}
	return (NULL);
}

void clearMulti(t_data *data)
{
	int	i;

	i = 0;
	g_ids = 0;
	cubism(data);
	while (i < THREADS)
	{
		if (pthread_create(&data->mutex[i], NULL, &gravity,
				data) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(data->mutex[i], NULL);
	g_ids = 0;
}

int	showframes(t_data *data)
{
	if (BAKED)
	{
		data->bakery.index++;
		if (data->bakery.index == FRAMES)
			data->bakery.backed = 1;
		if (!data->bakery.backed && data->bakery.index < FRAMES)
		{
			system("clear");
			printf("[%lf]\n", data->bakery.index / (double)FRAMES);
			render(data);
		}
		else
		{
			if (data->time)
			{
				gettimeofday(&data->later, NULL);
				printf("[%lf]\n", ft_to_sec(data->later) - ft_to_sec(data->now));
				data->time = 0;
			}
			if (data->bakery.index >= FRAMES)
				data->bakery.index = 0;
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->bakery.frames[data->bakery.index].img,0,0);
			data->bakery.index++;
		}
	}
	else
	{
		render(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->bakery.frames->img, 0,0);
		//clearMulti(data);
	}
	return (0);
}

void	create_threat(t_data *data)
{
	data->mutex = (pthread_t *)malloc(sizeof(pthread_t) * THREADS);
}

t_node	*selectCube(t_node *node, t_particule *particule)
{
	if (particule->pos.y <= node->center.y)
	{
		if (particule->pos.x <= node->center.x)
			return(node->next[0]);
		else
			return(node->next[1]);
	}
	else
	{
		if (particule->pos.x < node->center.x)
			return(node->next[2]);
		else
			return(node->next[3]);
	}
	return (NULL);
}

void	placeParticule(t_data *data, t_node *node, t_particule *particule, int level)
{
	node->level = level;
	if (!node->last)
	{
		node->mass++;
		placeParticule(data, selectCube(node, particule), particule, level * 2);
	}
	else if (node->last && node->mass != 0 && node->level <= 200)
	{
		node->mass++;
		newBranch(node);
		t_list *temp = node->particule;
		while (temp != NULL)
		{
			placeParticule(data, selectCube(node, temp->content), temp->content, 2 * level);
			temp = temp->next;
		}
		freeList(node->particule);
		node->particule = NULL;
		placeParticule(data, selectCube(node,particule), particule, level * 2);
		node->id = -1;
	}
	else if(node->last && (node->mass == 0 || node->level > 200))
	{
		node->mass++;
		if (node->particule->content == NULL)
			node->particule->content = particule;
		else
			ft_lstadd_back(&node->particule, ft_lstnew(particule));
	}
}


void *multiCubism(void *temp)
{
	int	i;
	int	temp_id;

	temp_id = g_ids;
	g_ids++;
	t_data *data = temp;
	i = 0;
	while(i < data->particules.max)
	{
		placeParticule(data, data->tree, &data->particules.array[i], 2);
		i += THREADS;
	}
	return (NULL);
}

void	multiCubismLauch(t_data *data, int boo)
{
	int	i;

	i = 0;
	if (boo)
		data->tree = newTree();
	data->tree->level = 2;
	g_ids = 0;
	while (i < THREADS)
	{
		if (pthread_create(&data->mutex[i], NULL, &multiCubism,
				data) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(data->mutex[i], NULL);
	g_ids = 0;
}

void	cubism(t_data *data)
{
	int	i;

	data->tree = newTree();
	i = 0;
	data->tree->level = 2;
	while (i < data->particules.max)
	{
		placeParticule(data, data->tree, &data->particules.array[i], 2);
		i++;
	}
}

void	calculateForce(t_data *data, t_particule particule, t_node *node, double dis)
{
	t_uv u;

	if (dis > 20)
	{
		u = uv_res(node->center, particule.pos);
		u = uv_mul(uv_normalized(u), node->mass / dis);
		data->particules.array[particule.id].u = uv_sum(data->particules.array[particule.id].u, u);
	}
}

void	calculateForce2(t_particule *particule1, double dis, t_uv vec)
{
	t_uv u;

	if (dis > 20)
	{
		u = vec;
		u = uv_mul(uv_normalized(u), 1 / dis);
		particule1->u = uv_sum(particule1->u, u);
	}
}

void	searchTree(t_data *data, t_particule *particule, t_node *node)
{
	double	dis;
	t_uv	vec;

	vec = uv_res(particule->pos, node->center);
	dis = uv_len(vec);
	if (dis > MINDIS / node->level && node->mass)
	{
		calculateForce(data, *particule, node, uv_relativ_dis(uv_res(particule->pos, node->center)));
	}
	else if (node->last && node->mass)
	{
		(void)data;
		t_list *temp;
		temp = node->particule;
		while (temp != NULL)
		{
			t_particule *temp2 = temp->content;
			vec = uv_res(temp2->pos, particule->pos);
			calculateForce2(particule, uv_relativ_dis(vec), vec);
			temp = temp->next;
		}
	}
	else if (!node->last)
	{
		searchTree(data, particule, node->next[0]);
		searchTree(data, particule, node->next[1]);
		searchTree(data, particule, node->next[2]);
		searchTree(data, particule, node->next[3]);
	}
}


int	insideRect(t_uv point, t_uv rightTop, t_uv botLeft)
{
	if (point.x < rightTop.x && point.x > botLeft.x && point.y < botLeft.y && point.y > rightTop.y)
		return(1);
	return (0);
}

int	intclamp(int min, int max, int value)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

void	wormholeForce(t_data *data, t_particule *particule)
{
	//t_uv u;
	t_uv vec;
	double	len;

	vec = uv_res(data->wormhole.pos1, particule->pos);
	len =  uv_len(vec);
	if (len > 0.5)
		particule->u = uv_sum(uv_mul(uv_normalized(vec), data->wormhole.force / len), particule->u);
	vec = uv_res(data->wormhole.pos2, particule->pos);
	len =  uv_len(vec);
	if (len > 0.5)
		particule->u = uv_res(particule->u, uv_mul(uv_normalized(vec), data->wormhole.force / uv_len(vec)));
}

int	insideCirc(t_uv pos, t_uv center, double radious)
{
	if (uv_len(uv_res(pos, center)) <= radious)
		return (1);
	return (0);
}

void	*gravity(void *temp)
{
	int	j;
	int	temp_id;
	t_uv	hold;

	temp_id = g_ids;
	g_ids++;
	t_data *data = temp;
	j = temp_id;
	while (j < data->particules.max)
	{
		searchTree(data, &data->particules.array[j], data->tree);
		wormholeForce(data, &data->particules.array[j]);
		j += THREADS;
	}
	//j = temp_id;
	/*while(j < data->particules.max)
	{
		data->bakery.frames->add[intclamp(0, WIDTH * HEIGH - 1,(int)data->particules.array[j].pos.y * WIDTH + (int)data->particules.array[j].pos.x)] = 0;
		j += THREADS;
	}
	usleep(100);*/
	j = temp_id;
	while (j < data->particules.max)
	{
		data->bakery.frames->add[intclamp(0, WIDTH * HEIGH - 1,(int)data->particules.array[j].pos.y * WIDTH + (int)data->particules.array[j].pos.x)] = 0;
		hold = uv_sum(data->particules.array[j].pos, data->particules.array[j].u);
		if (!insideRect(hold, uv(WIDTH, 0), uv(0, HEIGH)))
		{
			/*data->particules.array[j].u = uv_mul(data->particules.array[j].u, -1);*/data->particules.array[j].pos = uv(clamp(5, WIDTH - 5, (WIDTH / 2 - hold.x) + WIDTH / 2), clamp(5, HEIGH - 5, (HEIGH / 2 - hold.y) + HEIGH / 2));
			data->particules.array[j].u = uv_div(data->particules.array[j].u, 2);
		}
		else if (WORMHOLE && insideCirc(hold, data->wormhole.pos1, data->wormhole.radious))
		{
			data->particules.array[j].pos = hold;
			data->particules.array[j].pos.x += WIDTH / 2;
			data->particules.array[j].u = uv_div(uv_mul(data->particules.array[j].u, -1), 2);
		}
		else
			data->particules.array[j].pos = hold;
		data->bakery.frames->add[intclamp(0, WIDTH * HEIGH - 1, (int)data->particules.array[j].pos.y * WIDTH + (int)data->particules.array[j].pos.x)] += 16777215 / 10000 * (int)uv_len(data->particules.array[j].u); // /1000
		j += THREADS;
	}
	return (NULL);
}

void	setParticules(t_data *data, char *argv)
{
	int	fd;
	char	*line;
	int		len;
	int		i;

	len = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("Input file error\n");
		exit(0);
	}
	do
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n'|| line[0] == '\0')
			break ;
		len++;
		free(line);
	} while (1);
	data->particules.array = malloc(sizeof(t_particule) * (len + 1));
	if (!data->particules.array)
		exit(0);
	data->particules.max = len;
	fd = open(argv, O_RDONLY);
	i = 0;
	do
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n' || line[0] == '\0')
			break ;
		data->particules.array[i].id = i;
		data->particules.array[i].pos = getUv(line);
		data->particules.array[i].u = uv(0,0);
		free(line);
		i++;
	} while (1);
}

void	drawRectangule(t_data *data, int minX, int maxX, int minY, int maxY, int col)
{
	int	i;
	int	j;

	j = minY;
	while(j < maxY)
	{
		i = minX;
		while (i < maxX)
		{
			data->map.add[j * WIDTH + i] = col;
			i++;
		}
		j++;
	}
}

void	drawTree(t_data *data, t_node *node, int num)
{
	if (node->last)
		drawRectangule(data, node->botLeft.x, node->topRight.x, node->topRight.y, node->botLeft.y, convert_rgb(vector(num * 10,num * 10,num * 10)));
	else
	{
		drawTree(data, node->next[0], ++num);
		drawTree(data, node->next[1], ++num);
		drawTree(data, node->next[2], ++num);
		drawTree(data, node->next[3], ++num);
	}
}

void	backeryStart(t_data *data)
{
	int	i;
	
	i = 0;
	data->bakery.index = 0;
	data->bakery.backed = 0;
	if (BAKED)
	{
		while (i < FRAMES)
		{
			data->bakery.frames[i].img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGH);
			data->bakery.frames[i].add = (int *)mlx_get_data_addr(data->bakery.frames[i].img,
				&data->bakery.frames[i].bpp, &data->bakery.frames[i].w,
				&data->bakery.frames[i].endian);
			i++;
		}
	}
	else
	{
		data->bakery.frames[i].img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGH);
			data->bakery.frames[i].add = (int *)mlx_get_data_addr(data->bakery.frames[i].img,
				&data->bakery.frames[i].bpp, &data->bakery.frames[i].w,
				&data->bakery.frames[i].endian);
	}
}

void	set_wormhole(t_data *data)
{
	data->wormhole.pos1 = uv(WIDTH / 4, HEIGH / 2);
	data->wormhole.pos2 = uv(WIDTH / 4 * 3, HEIGH / 2);
	data->wormhole.force = 100;
	data->wormhole.radious = 100;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (0);
	init_mlx(&data);
	create_threat(&data);
	set_map(&data);
	setParticules(&data, argv[1]);
	backeryStart(&data);
	if (WORMHOLE)
		set_wormhole(&data);
	gettimeofday(&data.now, NULL);
	data.time = 1;
	(void)argv;
	(void)argc;
	mlx_loop_hook(data.mlx.mlx, showframes, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
