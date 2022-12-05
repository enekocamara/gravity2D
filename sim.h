/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:36:04 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/05 15:25:40 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGH 1000
# define WIDTH 1000
# define RES 10
# define THREADS 2
# define TIME 1

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define TAN45 0.75
# define SKBW	8192
# define SKBH	4096
# define SKBD	1365
# define SKBD2	682
#define MINDIS	1414 * 10
#define FRAMES 50
#define BAKED 0

# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

int g_ids;
int	g_ids2;

typedef struct s_uv
{
	double	x;
	double	y;
}t_uv;

typedef struct s_couple
{
	double	x;
	double	y;
	double	z;
}t_couple;

typedef struct s_img
{
	void	*img;
	int		*add;
	int		bpp;
	int		w;
	int		h;
	int		endian;
	int		*color;
	int		check;
}t_img;

typedef struct s_called
{
	double		dis;
	int			called;
}t_called;

typedef struct s_potential
{
	t_called	*sphere_p;
	t_called	*plane_p;
	t_called	*cilinder_p;
	t_called	*cone_p;
}t_potential;

typedef struct s_matrix1
{
	double	matrix[4];
}t_matrix1;

typedef struct s_matrix
{
	double	matrix[4][4];
}t_matrix;

typedef struct s_ray
{
	t_couple	origin;
	t_couple	direction;
	double		t;
}t_ray;

typedef struct s_cam
{
	t_couple	up;
	t_couple	right;
	t_couple	origin;
	t_couple	direction;
	t_couple	coord_up;
	t_couple	coord_up_n;
	t_couple	coord_down;
	t_couple	coord_down_n;
	t_couple	coord_left;
	t_couple	coord_left_n;
	t_couple	coord_right;
	t_couple	coord_right_n;
	double		ratio;
	double		fov;
	double		h;
	double		w;
}t_cam;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	int		img_index;
}t_mlx;

typedef struct s_thread
{
}t_thread;

struct s_node;

typedef struct s_particule
{
	t_uv	pos;
	t_uv	u;
	int		id;
	struct s_node	*node;
}t_particule;

typedef struct s_node
{
	int		mass;
	struct s_node *next[4];
	int		last;
	t_uv	topRight;
	t_uv	botLeft;
	t_uv	center;
	int		id;
	int		level;
	int		time;
	t_list	*particule;
}t_node;

typedef struct s_objects
{
	int			max;
	t_particule	*array;
}t_objects;

typedef struct s_bakery
{
	t_img	frames[FRAMES * BAKED + 1];
	int		index;
	int		backed;
}t_bakery;

typedef struct s_data
{
	t_img		map;
	t_mlx		mlx;
	t_node		*tree;
	t_objects	particules;
	pthread_t	*mutex;
	t_bakery	bakery;
	struct timeval	now;
	struct timeval	later;
	int				time;
}t_data;

/* ------ MAIN ------- */

void		free_data(t_data *data);

/* ------ ERROR --------*/

void		error(char *str, int *check, int exit_err);
int			input_error(char *str, char *str2, int *check, int exit_err);
void		free_input(t_data *data);
int			ft_close(t_data *data);
void		free_exit(t_data *data);

/* ------- PRINT -------*/

void		print_data(t_data *data);
void		print_vec(t_couple vec);

/* ------- GET_INPUT -------*/

void		mallocs(t_data *data, int *check);
void		get_input(t_data *data, char *argv, int check);
void		check_input(t_data *data, char **lines, int *check, int j);
void		alloc_elements(t_data *data, char **lines, int *check);

/* ------- READ_FILE ------- */

char		*get_file(int fd, int *check);
char		*read_in_loop(char **str, int fd, int filled, int *check);

/* ------- SET_SPACE ------- */

void		set_camera(t_data *data, char *line);
void		set_light(t_data *data, char *line);
void		set_ambient_light(t_data *data, char *line);
void		set_img(t_data *data, int *check);
void		set_axis_cam(t_data *data, int i);

/* ------- SET_SHAPES ------- */

void		set_sphere(t_data *data, char *line);
void		set_plane(t_data *data, char *line);
void		set_cylinder(t_data *data, char *line);
//void		set_disc(t_cilinder *cilinder);
void		set_cone(t_data *data, char *line);

/* ------- CHECK_SPACE ------- */

void		check_camera(t_data *data, char *line, int *check);
void		check_light(t_data *data, char *line, int *check);
void		check_ambient_light(char *line, int *check);
void		c_check_values_range(char *str, int *check, double min, double max);

/* ------- CHECK_SHAPES ------- */

void		check_sphere(t_data *data, char *line, int *check);
void		check_plane(t_data *data, char *line, int *check);
void		check_cylinder(t_data *data, char *line, int *check);
void		check_cone(t_data *data, char *line, int *check);

/* ------- CHECK_VALUES ------ */

int			check_double(char *num, int *check);
int			check_three(char *str, int *check);
void		check_rt(char *str, int *check);
void		check_values_range(char *str, int *check, double min, double max);
void		check_dbl_range(double value, int *check, double min, double max);

/* ------- INTERSECTION ------*/

//t_intersect	launch_intersect(t_ray *ray, t_shapes *elements, int times);
//int			launch_shadow(t_ray ray, t_shapes *elements, double dis);
//int			check_launch(double t, double dis, int called, int boo);
//void		init_intersect(t_intersect *intersect);

/* - GET_INTERSECT_SHAPES - */

//void		get_in_pl(t_intersect *in, t_plane *plane, t_ray ray);
//void		get_in_s(t_intersect *in, t_sphere *sph, t_couple nor, t_ray orig);
//void		get_in_c(t_intersect *in, t_cilinder *cil, t_ray orig, t_ray ray);
//void		get_disc(t_intersect *in, t_disc disc, t_ray orig);
//void		get_in_cn(t_intersect *in, t_cone *cone, t_ray orig, t_ray ray);

/* --- INTERSECT_SHAPES --- */

//void		in_sphere(t_intersect *in, t_ray ray, t_sphere *sph, t_ray orig);
//void		in_plane(t_intersect *in, t_ray ray, t_plane *plane);
//void		in_cil(t_intersect *in, t_ray ray, t_cilinder *cil, t_ray orig);
//int			in_disc(t_intersect *in, t_ray ray, t_disc *disc, t_ray orig);

/* - INTERSECT_SHAPES_AUX - */

//t_couple	get_normal_c(t_cilinder *cil, t_ray ray);
//double		get_det_c(t_couple *grades, double radious, t_ray ray);
//int			inside_disc(double radious, t_couple point, t_couple origin);
//void		in_cone(t_intersect *in, t_ray ray, t_cone *cone, t_ray orig);
//double		get_det_cn(t_couple *grades, t_ray ray);

/* ---- INTERSECT_LAUNCH --- */

//void		launch_in_s(t_intersect *in, t_ray *ray, t_shapes *elem, int boo);
//void		launch_in_p(t_intersect *in, t_ray *ray, t_shapes *elem, int boo);
//void		launch_in_cy(t_intersect *in, t_ray *ray, t_shapes *elem, int boo);
//void		launch_in_cn(t_intersect *in, t_ray *ray, t_shapes *elem, int boo);

/* ---- LAUNCH_SHADOW ---- */

//int			launch_shadow_s(t_ray ray, t_shapes *elements, double dis);
//int			launch_shadow_cy(t_ray ray, t_shapes *elements, double dis);
//int			launch_shadow_p(t_ray ray, t_shapes *elements, double dis);
//int			launch_shadow_cn(t_ray ray, t_shapes *elements, double dis);

/* ---- INTERSECT SH ---- */

//int			in_sphere_sh(t_ray ray, t_sphere *sphere, double dis);
//int			in_disc_sh(t_disc disc, t_ray orig, double dis);
//int			in_cil_sh(t_ray ray, t_cilinder *cil, t_ray orig, double dis);
//int			in_plane_sh(t_ray ray, t_plane *plane, double dis);
//int			in_cone_sh(t_ray ray, t_cone *cone, t_ray orig, double dis);

/*------- MATRIX_MATH -------*/

t_matrix	*matrix_mul(t_matrix *m1, t_matrix *m2);
t_couple	rotate(t_couple vec, t_matrix *matrix);
t_couple	translate(t_couple vec, t_matrix *matrix);
t_couple	antitranslate(t_couple vec, t_matrix *matrix);
t_ray		trans_ray(t_ray *ray, t_matrix *trans, t_matrix *rot);

/* ----- MATRIX_SET ----- */

t_matrix	*set_translation(t_couple point, t_couple distance);
t_matrix	set_rotate(double angle, t_couple vec1, t_couple vec2);
void		set_matrix(t_matrix *matrix);
void		init_m_1(t_couple vec, double last, t_matrix1 *m);
void		asign_rotate(t_matrix *m, double sino, double coseno, t_couple p);

/* -------- COLOR ---------- */

//t_couple	color(t_ray ray, t_shapes *elements, int times, double old_ref);
//t_couple	get_col(t_intersect *intersect, t_shapes *elements);
//double		all_ref(t_intersect intersect);
//int			convert_color(t_couple col);
//int			check_if_ref(t_intersect intersect);

/* ------ REBOUND --------- */

//t_couple	all_rebound(t_intersect intersect);
t_couple	rebound(t_couple ray, t_couple normal);

/* --------- MATH ---------- */

double		power(double x);
double		clamp(double min, double max, double value);
double		ft_abs(double num);
double		get_angle(t_couple vec1, t_couple vec2);
double		ft_to_sec(struct timeval time);

/* -------- COL_MATH -------- */

t_couple	col_to_01(t_couple col);
t_couple	col_to_255(t_couple col);
t_couple	gamm_correction(t_couple col);
t_couple	mix(t_couple col, t_couple col2, double grade);
int			convert_rgb(t_couple col);

/* ------ LIGHTING --------- */

//t_couple	lighting_p(t_intersect *in, t_shapes *elem, t_couple col);
//t_couple	lighting_s(t_intersect *in, t_shapes *elem, t_couple col);
//t_couple	lighting_c(t_intersect *in, t_shapes *elem, t_couple col);
//t_couple	lighting_cn(t_intersect *in, t_shapes *elem, t_couple col);

/* ----- POTENTIAL --------- */

//void		get_potential(t_shapes	*elements);
//void		set_potential(t_shapes	*elem, t_couple point);
//void		order(t_shapes *elem, t_called *potential1, int max, int check);
//void		init_called(t_shapes *elem);

/* --- POTENTIAL GET DIS --- */

//double		get_dis_s(t_sphere *sphere, t_couple point);
//double		get_dis_p(t_plane *plane, t_couple point);
//double		get_dis_cy(t_cilinder *cilinder, t_couple point);
//double		get_dis_cn(t_cone *cone, t_couple point);

/* --------- SWAP --------- */

//void		swap_sp(t_sphere **sp, t_called *called, int i);
//void		swap_plane(t_plane **plane, t_called *called, int i);
//void		swap_cy(t_cilinder **cil, t_called *called, int i);
//void		swap_cone(t_cone **cone, t_called *called, int i);

/* -------- COUPLE -------- */

t_couple	point(double x, double y, double z);
t_couple	vector(double x, double y, double z);
t_couple	copy_couple(t_couple original);
t_couple	get_couple(char *str);
t_ray		set_ray(t_couple origin, t_couple direction);

/* ------ COUPLE MATH 1 ----- */

t_couple	c_res(t_couple c1, t_couple c2);
t_couple	c_sum(t_couple c1, t_couple c2);
t_couple	c_mul(t_couple c1, double c2);
t_couple	c_div(t_couple vec, double n);
t_couple	c_mul_c(t_couple vec1, t_couple vec2);

/* ------ COUPLE MATH 2 ----- */

double		len2(t_couple vec);
double		len(t_couple vec);
//t_couple	get_point(t_intersect intersect, int boo);
t_couple	set_point(t_couple origin, t_couple direction, double t);
t_couple	c_clamp(double min, double max, t_couple value);

/* ------ COUPLE MATH 3 ----- */

void		normalize(t_couple *vec);
double		dot(t_couple vec1, t_couple vec2);
t_couple	cross(t_couple vec1, t_couple vec2);
t_couple	normalized(t_couple vec);

/* ------ INIT DATA ------ */

void		init_vars(t_data *data);
void		set_data(t_data *data, char *argv[]);
void		init_mlx(t_data *data);

/* -------- AUX --------- */

void		free2d(char **str);

/* ----- SHOOT ------- */
void		shoot(t_data *data);

/* ---- SKYBOX ------ */

//t_couple	skybox(t_shapes *elem, t_ray ray);
void		set_skybox(t_data *data);

/* --------- UV ---------- */

t_uv		uv(double x, double y);
t_uv		uv_res(t_uv uv1, t_uv uv2);
t_uv		uv_sum(t_uv uv1, t_uv uv2);
t_uv		uv_normalized(t_uv in);
t_uv		uv_mul(t_uv uv1, double num);
t_uv		uv_div(t_uv uv1, double num);
double		uv_len(t_uv in);
double		uv_relativ_dis(t_uv in);
t_uv		getUv(char *str);

//t_couple	get_color_sphere(t_shapes *elem, t_couple point, t_img texture, int index);
t_couple	int_to_col01(int temp);

/* --------- NODE ----------- */

t_node	*newNode(t_uv topRight, t_uv botLeft);
void		newBranch(t_node *node);
t_node *newTree(void);
void		destoyNode(t_node *node);
void	freeList(t_list *list);
void	destroyTree(t_node *node);

void	calculateForce2(t_particule *particule1, double dis, t_uv vec);

void	*gravity(void *temp);
void	drawTree(t_data *data, t_node *node, int num);
int		insideRect(t_uv point, t_uv rightTop, t_uv botLeft);
void	placeParticule(t_data *data, t_node *node, t_particule *particule, int level);
void	cubism(t_data *data);
void	multiDestroyTreeLaunch(t_data *data);

void	multiCubismLauch(t_data *data, int boo);
#endif
