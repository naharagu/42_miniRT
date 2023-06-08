/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:35:10 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/04 01:16:51 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HANDLER_H
# define KEY_HANDLER_H

# include "main.h"
# include "parse.h"
# include "raytrace.h"
# include <stdlib.h>
# include <math.h>

void	handle_zoom(int keycode, t_window *window);
void	handle_move_cross(int keycode, t_window *window);
void	handle_move_updown(int keycode, t_window *window);
void	handle_rotate_vertical(int keycode, t_window *window);
void	handle_rotate_horizontal(int keycode, t_window *window);

int		key_handler(int keycode, t_window *window);

#endif