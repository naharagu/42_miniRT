/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:50:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/12 20:17:55 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_in_range_double(double num, double min, double max)
{
	if (min <= num && num <= max)
		return (true);
	return (false);
}

bool	is_in_range_int(int num, int min, int max)
{
	if (min <= num && num <= max)
		return (true);
	return (false);
}

bool	is_in_range_color(t_vec3 color)
{
	if (is_in_range_int(color.x, 0, 255) == true \
		&& is_in_range_int(color.y, 0, 255) == true \
		&& is_in_range_int(color.z, 0, 255) == true)
		return (true);
	return (false);
}
