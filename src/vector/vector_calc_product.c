/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc_product.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:28 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 15:46:42 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3_multiply_scalar(t_vec3 a, double b)
{
	return (vec3_create(a.x * b, a.y * b, a.z * b));
}

double	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
//内積

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.y * b.z - a.z - b.y, a.z * b.x - a.x - b.z, a.x * b.y
			- a.y * b.x));
}
//外積

double	vec3_magnitude(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
//ノルム

double	vec3_magnitude_squared(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}
