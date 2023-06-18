/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:56 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/12 20:16:58 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "vector.h"

bool	is_in_range_double(double num, double min, double max);
bool	is_in_range_int(int num, int min, int max);
bool	is_in_range_color(t_vec3 color);

#endif
