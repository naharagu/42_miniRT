/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:11 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 00:38:52 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void	set_color(double r, double g, double b, t_vec3 *color)
{
	color->x = r;
	color->y = g;
	color->z = b;
	return ;
}

int	get_color_in_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.x);
	g = (int)(color.y);
	b = (int)(color.z);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}
