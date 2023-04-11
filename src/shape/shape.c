/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/10 22:40:07 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "vector.h"
#include <stddef.h>

void	init_shape(t_shape *shapes)
{
	shapes->type = SPHERE;
	shapes->center = (t_vec3){0, 0, 5};
	shapes->radius = 0.7;
	shapes->next = NULL;
}
