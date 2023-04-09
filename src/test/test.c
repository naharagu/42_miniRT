/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:00:18 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/09 21:45:41 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "color.h"

void	print_color(t_color color)
{
	printf("r: %f, g: %f, b: %f\n", color.x, color.y, color.z);
}
