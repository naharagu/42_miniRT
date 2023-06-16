/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:48:45 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/16 20:16:20 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_map.h"

static t_vec3	cylinder_vec3(t_shape *shape, size_t idx_x)
{
	double	pi_x;	
	t_vec3	ret;

	pi_x = 2 * M_PI * idx_x / (double)shape->bump_div;
	ret = vec3_rotate(shape->unit_x, vec3_multiply_scalar(shape->unit_y, -1), pi_x);
	return (ret);
}

static t_vec3	calc_cylinder_b_normal(t_shape *shape, size_t idx_x)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	b_normal;

	a = cylinder_vec3(shape, idx_x);
	b = cylinder_vec3(shape, idx_x + 1);
	b_normal = vec3_normalize(vec3_addition(a, b));
	return (b_normal);
}

void	bump_cylinder(t_shape *shape)
{
	size_t	idx_x;
	size_t	idx_y;

	idx_x = 0;
	while (idx_x < shape->bump_div)
	{
		idx_y = 0;
		while (idx_y < shape->bump_div)
		{
			add_bump_map(shape, calc_cylinder_b_normal(shape, idx_x));
			idx_y++;
		}
		idx_x++;
	}
}
