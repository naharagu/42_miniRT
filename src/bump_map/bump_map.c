/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 07:20:42 by saikeda           #+#    #+#             */
/*   Updated: 2023/06/06 22:15:22 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_map.h"

void	add_bump_map(t_shape *shape, t_vec3 b_normal)
{
	t_bump_map	*new;
	t_bump_map	*tmp;

	new = malloc(sizeof(t_bump_map));
	if (new == NULL)
		put_error_and_exit("Miss allocate");
	new->b_normal = b_normal;
	new->next = NULL;
	if (shape->bump_map == NULL)
		shape->bump_map = new;
	else
	{
		tmp = shape->bump_map;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	bump_map(t_window *window)
{
	t_shape	*tmp;

	tmp = window->scene->shapes;
	while (tmp != NULL)
	{
		if (tmp->bump_flag == true && tmp->type == SPHERE)
			bump_sphere(tmp);
		tmp = tmp->next;
	}
}
