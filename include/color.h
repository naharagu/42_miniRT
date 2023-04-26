/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:37 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/26 08:40:26 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "vector.h"

typedef struct s_vec3	t_color;

void	set_color(double r, double g, double b, t_color *color);
int		get_color_in_int(t_color color);

#endif