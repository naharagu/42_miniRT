/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:49 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/29 13:31:24 by naharagu         ###   ########.fr       */
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
# define ALPHA 2
# define EPSILON 0.001953125

typedef struct s_scene	t_scene;
typedef struct s_window	t_window;
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
	ssize_t				index;
	double				distance;
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
	double	Dvv;
	double	Dsv;
	double	Dpv;
	double	Dss;
	double	Dps;
	double	Dpp;
}			t_discriminant;

t_color		shading(t_ray ray, t_intersect intersect, t_scene *scene);
void		raytrace(t_window *window);
bool		calculate_intersect_point(t_ray *ray, t_intersect *intersect, t_scene *scene, ssize_t intersect_index);

#endif