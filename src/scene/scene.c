/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/19 23:08:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "shape.h"
#include "vector.h"
#include "libft.h"
#include <stdlib.h>

void	init_scene(t_scene *scene)
{
	scene->ambient_color = (t_color){255, 255, 255};
	scene->ambient_ratio = 0.001;
	scene->camera.origin = (t_vec3){0, 0, -5};
	scene->light.origin = (t_vec3){-5, 5, -5};
	scene->shapes = ft_calloc(1, sizeof(t_shape));
	if (!scene->shapes)
		exit(1);
	init_shape(scene->shapes);
}
