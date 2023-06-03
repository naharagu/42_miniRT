/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:52 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 00:41:10 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "parse.h"
# include "vector.h"
# include "raytrace.h"
# include <unistd.h>
# include <stdbool.h>

typedef struct s_shape		t_shape;
typedef struct s_scene		t_scene;
typedef struct s_ray		t_ray;
typedef struct s_intersect	t_intersect;

enum					e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
};

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
	t_vec3				color;
};

// shape_utils.c
t_shape					*shape_lst_last(t_shape *shapes);
t_shape					*shape_lst_add(t_scene *scene);

// sphere.c
bool					intersect_sphere(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// plane.c
bool					intersect_plane(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// cylinder.c
bool					intersect_cylinder(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

// cone.c
bool					intersect_cone(t_shape *shape, t_ray *ray, \
								t_intersect *intersect);

#endif