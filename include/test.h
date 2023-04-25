/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:54 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:04:55 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "color.h"
# include "parse.h"
# include <stdio.h>

void	print_color(t_color color);
void	print_t_scene(t_scene *scene);
void	print_t_shape(t_shape *shape);

#endif
