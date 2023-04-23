/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/23 22:10:32 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include "parse.h"
#include "color.h"
#include "libft.h"
#include <math.h>

int	key_handler(int key, t_window *window)
{
	// dprintf(STDERR_FILENO, "key: %d\n", key);//delete later
	if (key == ESC)
	{
		mlx_loop_end(window->mlx);
		exit(0);
	}
	return (0);
}

void	loop_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	mlx_key_hook(window->mlx_win, key_handler, window);
	mlx_loop(window->mlx);
}

int	main(int argc, char **argv)
{
	t_window	window;
	t_scene scene;

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
