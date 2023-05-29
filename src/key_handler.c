/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:21:39 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/29 13:24:27 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "raytrace.h"
#include <stdlib.h>
#include <math.h>

static void	handle_zoom(int keycode, t_window *window)
{
	if (keycode == '1' && window->scene->camera.fov <= 179)
		window->scene->camera.fov += 1;
	else if (keycode == '2' && window->scene->camera.fov >= 1)
		window->scene->camera.fov -= 1;
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_move(int keycode, t_window *window)
{
	if (keycode == 'w')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->scene->camera.dir);
	else if (keycode == 's')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, \
		window->scene->camera.dir);
	else if (keycode == 'd')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sx);
	else if (keycode == 'a')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sx);
	else if (keycode == '9')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sy);
	else if (keycode == '0')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sy);
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_vertical(int keycode, t_window *window)
{
	if (keycode == 'i')
		window->scene->camera.dir = \
			vec3_normalize(vec3_addition(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	else if (keycode == 'k')
		window->scene->camera.dir = \
			vec3_normalize(vec3_subtraction(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	window->screen.e_sy = \
	vec3_normalize(vec3_cross_product(window->scene->camera.dir, \
	window->screen.e_sx));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_horizontal(int keycode, t_window *window)
{
	if (keycode == 'l')
		window->scene->camera.dir = \
			vec3_normalize(vec3_addition(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	else if (keycode == 'j')
		window->scene->camera.dir = \
			vec3_normalize(vec3_subtraction(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	window->screen.e_sx = \
	vec3_normalize(vec3_cross_product(window->screen.e_sy, \
	window->scene->camera.dir));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

int	key_handler(int keycode, t_window *window)
{
	if (keycode == ESC)
		exit_window("ESC");
	else if (keycode == '1' || keycode == '2')
		handle_zoom(keycode, window);
	else if (keycode == 'w' || keycode == 's' || keycode == 'd' || \
			keycode == 'a' || keycode == '9' || keycode == '0')
		handle_move(keycode, window);
	else if (keycode == 'i' || keycode == 'k')
		handle_vertical(keycode, window);
	else if (keycode == 'l' || keycode == 'j')
		handle_horizontal(keycode, window);
	else
		return (0);
	raytrace(window);
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	return (0);
}
