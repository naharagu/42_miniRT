/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/21 16:17:21 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "raytrace.h"
#include <stdlib.h>
#include "test.h"

static int	exit_window(const char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

static int	key_handler(int keycode, t_window *window)
{
	if (keycode == ESC)
	{
		mlx_loop_end(window->mlx);
		exit_window("ESC");
	}
	// 縮小
	else if (keycode == '1')
	{
		if (window->scene->camera.fov < 179)
			window->scene->camera.fov += 1;
	}
	// 拡大
	else if (keycode == '2')
	{
		if (window->scene->camera.fov > 1)
			window->scene->camera.fov -= 1;
	}
	// 前進
	else if (keycode == 'w')
		window->scene->camera.origin = vec3_addition(window->scene->camera.origin, window->scene->camera.dir);
	// 後退
	else if (keycode == 's')
		window->scene->camera.origin = vec3_subtraction(window->scene->camera.origin, window->scene->camera.dir);
	// 右
	else if (keycode == 'd')
		window->scene->camera.origin = vec3_addition(window->scene->camera.origin, window->screen.e_sx);
	// 左
	else if (keycode == 'a')
		window->scene->camera.origin = vec3_subtraction(window->scene->camera.origin, window->screen.e_sx);
	// 上
	else if (keycode == '9')
		window->scene->camera.origin = vec3_addition(window->scene->camera.origin, window->screen.e_sy);
	// 下
	else if (keycode == '0')
		window->scene->camera.origin = vec3_subtraction(window->scene->camera.origin, window->screen.e_sy);
	// 上回転
	else if (keycode == 'i')
		window->scene->camera.dir = vec3_normalize(vec3_addition(window->scene->camera.dir, vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	// 下回転
	else if (keycode == 'k')
		window->scene->camera.dir = vec3_normalize(vec3_subtraction(window->scene->camera.dir, vec3_multiply_scalar(window->screen.e_sy, 0.05)));
	// 右回転
	else if (keycode == 'l')
		window->scene->camera.dir = vec3_normalize(vec3_addition(window->scene->camera.dir, vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	// 左回転
	else if (keycode == 'j')
		window->scene->camera.dir = vec3_normalize(vec3_subtraction(window->scene->camera.dir, vec3_multiply_scalar(window->screen.e_sx, 0.05)));
	printf("dir %f, %f, %f\n", window->scene->camera.dir.x, window->scene->camera.dir.y, window->scene->camera.dir.z);
	printf("org %f, %f, %f\n", window->scene->camera.origin.x, window->scene->camera.origin.y, window->scene->camera.origin.z);
	raytrace(window);
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	return (0);
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

	init_window(&window);
	parse_rt_file(argc, argv, &scene);
	window.scene = &scene;
	raytrace(&window);
	loop_window(&window);
	return (0);
}

// __attribute__((destructor))
// static void destructor(void)
// {
//     system("leaks -q miniRT");
// }
