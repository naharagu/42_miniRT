/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:52 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/15 22:26:38 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "parse.h"
# include "vector.h"
# include "raytrace.h"
# include "bump_map.h"
# include <unistd.h>
# include <stdbool.h>

typedef struct s_shape			t_shape;
typedef struct s_scene			t_scene;
typedef struct s_ray			t_ray;
typedef struct s_intersect		t_intersect;
typedef struct s_window			t_window;
typedef struct s_bump_map		t_bump_map;
typedef struct s_discriminant	t_discriminant;

enum					e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
};

typedef struct	s_color
{
	t_vec3				color;
	struct s_color		*next;
} t_color;

struct					s_shape
{
	enum e_shape_type	type;
	ssize_t				index;
	t_shape				*next;
	t_vec3				center;
	t_vec3				orientation;
	t_vec3				normal;
	double				radius;
	double				height;
	t_color				*colors;
	size_t				colors_cnt;
	size_t				color_div;
	bool				bump_flag;
	size_t				bump_div;
	t_bump_map			*bump_map;
	t_vec3				unit_x;
	t_vec3				unit_y;
	t_vec3				unit_z;
};

// shape_utils.c
t_shape					*shape_lst_last(t_shape *shapes);
t_shape					*shape_lst_add(t_scene *scene);

// sphere.c
void					checkerboard_color(t_shape *shape, t_intersect *intersect);
size_t					calc_circle_index(double pi, double division);
bool					intersect_sphere(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// plane.c
bool					intersect_plane(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// cylinder.c
void					calc_intersect_cylinder(t_shape *shape, t_intersect *intersect, t_discriminant *d);
bool					intersect_cylinder(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// cone.c
bool					intersect_cone(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// shapes_unit.c
void					shapes_unit(t_window *window);

#endif