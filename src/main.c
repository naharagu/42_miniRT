/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/20 14:40:48 by saikeda          ###   ########.fr       */
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
	raytrace(&window, &scene);
	loop_window(&window);
	return (0);
}

// __attribute__((destructor))
// static void destructor(void)
// {
//     system("leaks -q miniRT");
// }
