/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:14:07 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/23 21:58:45 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raytrace.h"
#include "parse.h"
#include "color.h"
#include "libft.h"
#include <math.h>

int	key_handler(int key, t_world *world)
{
	// dprintf(STDERR_FILENO, "key: %d\n", key);//delete later
	if (key == ESC)
	{
		mlx_loop_end(world->mlx);
		exit(0);
	}
	return (0);
}

void	loop_window(t_world *world)
{
	mlx_put_image_to_window(world->mlx, world->mlx_win, world->img, 0, 0);
	mlx_key_hook(world->mlx_win, key_handler, world);
	mlx_loop(world->mlx);
}

int	main(int argc, char **argv)
{
	t_world	world;
	t_scene scene;

	parse_rt_file(argc, argv, &world, &scene);
	raytrace(&world, &scene);
	loop_window(&world);
	return (0);
}

// __attribute__((destructor))
// static void destructor(void)
// {
//     system("leaks -q miniRT");
// }
