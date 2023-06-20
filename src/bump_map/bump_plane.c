/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 07:54:00 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/20 13:01:32 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_map.h"

static double	calc_rotate_pi(t_shape *shape, size_t idx)
{
	double	pi;

	pi = ceil((double)idx / 2.0) * M_PI / 2.0 * -1.0 / (double)shape->bump_div;
	return (pi);
}

static t_vec3	calc_plane_b_normal(t_shape *shape, size_t idx_x, size_t idx_y)
{
	t_vec3	b_normal;

	b_normal = \
	vec3_rotate(shape->normal, shape->unit_x, calc_rotate_pi(shape, idx_x));
	b_normal = \
	vec3_rotate(b_normal, shape->unit_z, calc_rotate_pi(shape, idx_y));
	return (b_normal);
}

void	bump_plane(t_shape *shape)
{
	size_t	idx_x;
	size_t	idx_y;

	idx_x = 0;
	while (idx_x < shape->bump_div)
	{
		idx_y = 0;
		while (idx_y < shape->bump_div)
		{
			add_bump_map(shape, calc_plane_b_normal(shape, idx_x, idx_y));
			idx_y++;
		}
		idx_x++;
	}
}
