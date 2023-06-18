/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:51:14 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/12 18:23:53 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	convert_rgb(t_vec3 color)
{
	return (vec3_create(color.x / 255.0, color.y / 255.0, color.z / 255.0));
}
