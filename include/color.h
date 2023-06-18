/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:37 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/04 00:39:12 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "vector.h"

// typedef struct s_vec3	t_color;

void	set_color(double r, double g, double b, t_vec3 *color);
int		get_color_in_int(t_vec3 color);

#endif