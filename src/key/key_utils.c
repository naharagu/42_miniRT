/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:29:34 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/02 23:36:04 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_handler.h"

void	handle_zoom(int keycode, t_window *window)
{
	if (keycode == '1' && window->scene->camera.fov <= 179)
		window->scene->camera.fov += 1;
	else if (keycode == '2' && window->scene->camera.fov >= 1)
		window->scene->camera.fov -= 1;
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

void	handle_move_cross(int keycode, t_window *window)
{
	t_vec3	vec3;

	if (keycode == 'w')
		vec3 = \
		vec3_addition(window->scene->camera.origin, window->scene->camera.dir);
	else if (keycode == 's')
		vec3 = \
		vec3_subtraction(window->scene->camera.origin, \
		window->scene->camera.dir);
	else if (keycode == 'd')
		vec3 = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sx);
	else
		vec3 = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sx);
	if (check_range_vec3(vec3) == true)
		window->scene->camera.origin = vec3;
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

void	handle_move_updown(int keycode, t_window *window)
{
	t_vec3	vec3;

	if (keycode == '9')
		vec3 = \
		vec3_addition(window->scene->camera.origin, window->screen.e_sy);
	else
		vec3 = \
		vec3_subtraction(window->scene->camera.origin, window->screen.e_sy);
	if (check_range_vec3(vec3) == true)
		window->scene->camera.origin = vec3;
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

void	handle_rotate_vertical(int keycode, t_window *window)
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

void	handle_rotate_horizontal(int keycode, t_window *window)
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