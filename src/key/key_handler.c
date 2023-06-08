/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:21:39 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/02 23:35:52 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_handler.h"

int	key_handler(int keycode, t_window *window)
{
	if (keycode == ESC)
		exit_window("ESC");
	else if (keycode == '1' || keycode == '2')
		handle_zoom(keycode, window);
	else if (keycode == 'w' || keycode == 's' || keycode == 'd' || \
			keycode == 'a')
		handle_move_cross(keycode, window);
	else if (keycode == '9' || keycode == '0')
		handle_move_updown(keycode, window);
	else if (keycode == 'i' || keycode == 'k')
		handle_rotate_vertical(keycode, window);
	else if (keycode == 'l' || keycode == 'j')
		handle_rotate_horizontal(keycode, window);
	else
		return (0);
	raytrace(window);
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	return (0);
}
