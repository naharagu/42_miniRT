/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:14:18 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/06 22:19:20 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMP_MAP_H
# define BUMP_MAP_H

# include "shape.h"
# include "exit.h"
# include <stdlib.h>
# include <math.h>

typedef struct s_shape		t_shape;
typedef struct s_window		t_window;

typedef struct	s_bump_map
{
	t_vec3				b_normal;
	struct s_bump_map	*next;
} t_bump_map;

void	add_bump_map(t_shape *shape, t_vec3 b_normal);
void	bump_map(t_window *window);

void	bump_sphere(t_shape *shape);

#endif