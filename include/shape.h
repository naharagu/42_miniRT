/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:52 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:04:53 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "color.h"
# include "parse.h"
# include "vector.h"
# include <stdbool.h>

typedef struct s_shape	t_shape;
typedef struct s_scene	t_scene;

enum					e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

struct					s_shape
{
	enum e_shape_type	type;
	t_shape				*next;
	t_vec3				center;
	t_vec3				orientation;
	double				radius;
	t_color				color;
};

// shape_utils.c
t_shape					*shape_lst_last(t_shape *shapes);
t_shape					*shape_lst_add(t_scene *scene);

// sphere.c
bool					intersect_sphere(t_shape *shape, t_vec3 *ray,
							t_scene *scene);

#endif