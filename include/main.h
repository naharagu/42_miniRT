/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:42 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/23 07:05:00 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "mlx.h"
# include "vector.h"
# include <stdio.h>

# define HEIGHT 400
# define WIDTH 400
# define ESC 65307
# define LIMIT_RANGE 1000
# define LIMIT_TOP 100000
# define LIMIT_LIGHTS 3
# define LIMIT_SHAPES 20
# define LIMIT_COLORS 5
# define LIMIT_DIVISION 20

typedef struct s_screen
{
	t_vec3	center;
	t_vec3	e_sx;
	t_vec3	e_sy;
}	t_screen;
typedef struct s_scene	t_scene;

struct s_window
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_screen	screen;
	t_scene		*scene;
};
typedef struct s_window	t_window;

int	key_handler(int keycode, t_window *window);
int	exit_window(const char *msg);

#endif
