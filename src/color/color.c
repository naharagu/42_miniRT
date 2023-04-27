/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:11 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/27 19:13:31 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void	set_color(double r, double g, double b, t_color *color)
{
	color->x = r;
	color->y = g;
	color->z = b;
	return ;
}

int	get_color_in_int(t_color color)
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
