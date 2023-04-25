/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:49 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:09:13 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "color.h"
# include "main.h"
# include "parse.h"
# include "vector.h"
# include <stdbool.h>

# define K_DIFFUSE 0.69
# define K_SPECULAR 0.3
# define ALPHA 2

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}			t_ray;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	t2;
}			t_discriminant;

t_color		shading(t_scene *scene, t_vec3 ray);
void		raytrace(t_window *window, t_scene *scene);
bool		calculate_intersect_point(t_scene *scene, t_vec3 *ray);

#endif