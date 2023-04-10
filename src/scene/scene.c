/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/10 10:12:04 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"

void	init_scene(t_scene *scene)
{
	scene->ambient_color = (t_color){255, 255, 255};
	scene->ambient_ratio = 0.001;
	scene->camera = (t_vec3){0, 0, -5};
	scene->light = (t_vec3){-5, 5, -5};
	scene->object = (t_vec3){0, 0, 5};
}
