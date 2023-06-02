/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/02 22:58:42 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "raytrace.h"
#include <stdlib.h>
#include <math.h>

static void	init_screen(t_window *window)
{
	t_vec3	vup;
	double	e_sx_norm;

	vup = vec3_normalize(vec3_subtraction((t_vec3){0, 100000, 0}, \
						window->scene->camera.origin));
	window->screen.e_sx = \
		vec3_normalize(vec3_cross_product(vup, window->scene->camera.dir));
	e_sx_norm = vec3_dot_product(window->screen.e_sx, window->screen.e_sx);
	if (e_sx_norm < 1.0 - EPSILON || 1.0 + EPSILON < e_sx_norm)
	{
		window->screen.e_sx.x = 1;
		window->screen.e_sx.y = 0;
		window->screen.e_sx.z = 0;
	}
	window->screen.e_sy = \
		vec3_normalize(vec3_cross_product(window->scene->camera.dir, \
											window->screen.e_sx));
	window->screen.center = vec3_addition(window->scene->camera.origin, \
		vec3_multiply_scalar(window->scene->camera.dir, \
		((double)WIDTH / 2 / tan(window->scene->camera.fov / 2 / 180 * M_PI))));
}

static int	loop_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	mlx_hook(window->mlx_win, 2, 1L << 0, key_handler, window);
	mlx_hook(window->mlx_win, 12, 1L << 15, loop_window, window);
	mlx_hook(window->mlx_win, 17, 0L, exit_window, "Window closed");
	mlx_loop(window->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window	window;
	t_scene		scene;

	parse_rt_file(argc, argv, &scene);
	init_window(&window);
	window.scene = &scene;
	init_screen(&window);
	raytrace(&window);
	loop_window(&window);
	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}
