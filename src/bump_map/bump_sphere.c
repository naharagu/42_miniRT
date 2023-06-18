/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:13:19 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/06 22:21:46 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_map.h"

static t_vec3	sphere_vec3(t_shape *shape, size_t idx_x, size_t idx_y)
{
	double	pi_x;	
	double	pi_y;
	t_vec3	ret;

	pi_x = 2 * M_PI * idx_x / (double)shape->bump_div;
	ret = vec3_rotate(shape->unit_z, shape->unit_y, pi_x);
	pi_y = 2 * M_PI * (idx_y / (double)shape->bump_div);
	ret = vec3_rotate(shape->unit_y, vec3_multiply_scalar(ret, -1), pi_y);
	return (ret);
}

static t_vec3	calc_sphere_b_normal(t_shape *shape, size_t idx_x, size_t idx_y)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	b_normal;

	a = sphere_vec3(shape, idx_x, idx_y);
	b = sphere_vec3(shape, idx_x, idx_y + 1);
	if (idx_y != 0)
		c = sphere_vec3(shape, idx_x + 1, idx_y);
	else
		c = sphere_vec3(shape, idx_x + 1, idx_y + 1);
	b_normal = vec3_normalize(vec3_cross_product(vec3_subtraction(a, b), \
				vec3_subtraction(a, c)));
	return (b_normal);
}

void	bump_sphere(t_shape *shape)
{
	size_t	idx_x;
	size_t	idx_y;

	idx_x = 0;
	while (idx_x < shape->bump_div)
	{
		idx_y = 0;
		while (idx_y < shape->bump_div)
		{
			add_bump_map(shape, calc_sphere_b_normal(shape, idx_x, idx_y));
			idx_y++;
		}
		idx_x++;
	}
}
