/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:45 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 21:57:01 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"

static bool	intersect_helper(t_shape *shape, t_vec3 *ray, t_scene *scene)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray, scene));
	return (false);
}

bool	calculate_intersect_point(t_scene *scene, t_vec3 *ray)
{
	return (intersect_helper(scene->shapes, ray, scene));
}
