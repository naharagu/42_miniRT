/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:13:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/09 18:15:58 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCENE_H
# define SCENE_H

# include "vector.h"

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	orientation;
	double	fov;
}			t_camera;

typedef struct s_light
{
	t_vec3	origin;
	double	ratio;
	t_vec3	color;
}			t_light;

typedef struct s_hit
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}			t_hit;

#endif