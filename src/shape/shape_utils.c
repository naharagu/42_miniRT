/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/20 09:23:28 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "test.h"

t_shape	*shape_lst_last(t_shape *shapes)
{
	if (shapes == NULL)
		return (NULL);
	while (shapes->next)
		shapes = shapes->next;
	return (shapes);
}

t_shape	*shape_lst_add(t_scene *scene)
{
	t_shape	*tmp;

	if (scene->shapes == NULL)
	{
		scene->shapes = (t_shape *)ft_calloc(1, sizeof(t_shape));
		if (scene->shapes == NULL)
			put_error_and_exit("Failed to malloc");
		scene->shapes->index = 0;
		scene->shapes->next = NULL;
		return (scene->shapes);
	}
	else
	{
		tmp = shape_lst_last(scene->shapes);
		tmp->next = (t_shape *)ft_calloc(1, sizeof(t_shape));
		if (tmp->next == NULL)
			put_error_and_exit("Failed to malloc");
		tmp->next->index = tmp->index + 1;
		tmp->next->next = NULL;
		return (tmp->next);
	}
}
