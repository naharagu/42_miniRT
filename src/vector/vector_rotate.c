/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 07:18:49 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/06 22:21:32 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

static double	diagonal(double x, double pi)
{
	return (cos(pi) + (pow(x, 2) * (1 - cos(pi))));
}

static double	off_diagonal(double x, double y, double z, double pi)
{
	return ((x * y * (1 - cos(pi))) - (z * sin(pi)));
}

t_vec3	vec3_rotate(t_vec3 o, t_vec3 n, double pi)
{
	t_vec3	ret;
	double	xyz;
	double	yzx;
	double	zxy;

	xyz = off_diagonal(n.x, n.y, n.z, pi);
	yzx = off_diagonal(n.y, n.z, n.x, pi);
	zxy = off_diagonal(n.z, n.x, n.y, pi);
	ret.x = vec3_dot_product(vec3_create(diagonal(n.x, pi), xyz, zxy), o);
	ret.y = vec3_dot_product(vec3_create(xyz, diagonal(n.y, pi), yzx), o);
	ret.z = vec3_dot_product(vec3_create(zxy, yzx, diagonal(n.z, pi)), o);
	return (ret);
}
