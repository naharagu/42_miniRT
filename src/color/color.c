/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:11 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/09 18:57:55 by naharagu         ###   ########.fr       */
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
	return ((r << 16) + (g << 8) + b);
}
