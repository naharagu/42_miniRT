/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:49 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/20 23:30:15 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "main.h"
# include "color.h"
# include "parse.h"
# include "vector.h"
# include <unistd.h>
# include <stdbool.h>

# define K_DIFFUSE 0.69
# define K_SPECULAR 0.3
# define ALPHA 10

typedef struct s_scene		t_scene;
typedef struct s_window		t_window;
typedef struct s_light		t_light;
typedef enum e_shape_type	t_shape_type;
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	t_vec3	screen_center;
}			t_ray;

typedef struct s_intersect
{
	t_vec3				point;
	t_vec3				normal;
	t_vec3				color;
	t_vec3				calc_color;
	t_shape_type		type;
	ssize_t				index;
	double				distance;
	t_vec3				pro_x;
	t_vec3				pro_y;
	double				pi_x;
	double				pi_y;
	size_t				color_idx_x;
	size_t				color_idx_y;
	bool				bump;
	t_vec3				b_normal;
	size_t				bump_idx_x;
	size_t				bump_idx_y;
}						t_intersect;

typedef struct s_discriminant
{
	t_vec3	so;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	t2;
	double	vv;
	double	sv;
	double	pv;
	double	ss;
	double	ps;
	double	pp;
}			t_discriminant;

t_vec3		shading(t_ray *ray, t_intersect *intersect, t_scene *scene);
void		raytrace(t_window *window);
void		bump_map(t_window *window);
bool		calculate_intersect_point(t_ray *ray, t_intersect *intersect, \
			t_scene *scene, ssize_t intersect_index);
bool		shadow_intersect(t_intersect *intersect, \
									t_scene *scene, t_light *light);

t_vec3		convert_rgb(t_vec3 color);

#endif