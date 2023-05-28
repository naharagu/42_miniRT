/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:21:39 by saikeda           #+#    #+#             */
/*   Updated: 2023/05/28 22:31:58 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "raytrace.h"
#include <stdlib.h>
#include <math.h>

static void	handle_zoom(int keycode, t_window *window)
{
	// 縮小
	if (keycode == '1' && window->scene->camera.fov <= 179)
		window->scene->camera.fov += 1;
	// 拡大
	else if (keycode == '2' && window->scene->camera.fov >= 1)
		window->scene->camera.fov -= 1;
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_move(int keycode, t_window *window)
{
	// 前進
	if (keycode == 'w')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->scene->camera.dir);
	// 後退
	else if (keycode == 's')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, window->scene->camera.dir);
	// 右
	else if (keycode == 'd')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sx);
	// 左
	else if (keycode == 'a')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sx);
	// 上
	else if (keycode == '9')
		window->scene->camera.origin = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sy);
	// 下
	else if (keycode == '0')
		window->scene->camera.origin = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sy);
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_vertical(int keycode, t_window *window)
{
	// 上回転
	if (keycode == 'i')
		window->scene->camera.dir = \
			vec3_normalize(vec3_addition(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	// 下回転
	else if (keycode == 'k')
		window->scene->camera.dir = \
			vec3_normalize(vec3_subtraction(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	window->screen.e_sy = \
	vec3_normalize(vec3_cross_product(window->scene->camera.dir, window->screen.e_sx));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static void	handle_horizontal(int keycode, t_window *window)
{
	// 右回転
	if (keycode == 'l')
		window->scene->camera.dir = \
			vec3_normalize(vec3_addition(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	// 左回転
	else if (keycode == 'j')
		window->scene->camera.dir = \
			vec3_normalize(vec3_subtraction(window->scene->camera.dir, \
			vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	window->screen.e_sx = \
	vec3_normalize(vec3_cross_product(window->screen.e_sy, window->scene->camera.dir));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

int	key_handler(int keycode, t_window *window)
{
	if (keycode == ESC)
		exit_window("ESC");
	// 拡大縮小
	else if (keycode == '1' || keycode == '2')
		handle_zoom(keycode, window);
	else if (keycode == 'w' || keycode == 's' || keycode == 'd' || \
			keycode == 'a' || keycode == '9' || keycode == '0')
		handle_move(keycode, window);
	// 上下回転
	else if (keycode == 'i' || keycode == 'k')
		handle_vertical(keycode, window);
	// 左右回転
	else if (keycode == 'l' || keycode == 'j')
		handle_horizontal(keycode, window);
	else
		return (0);
	raytrace(window);
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	return (0);
}
