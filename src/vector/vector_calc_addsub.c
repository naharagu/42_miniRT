/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc_addsub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:28 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/08 10:23:09 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_addition(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_subtraction(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x - b.x, a.y - b.y, a.z - b.z));
}
