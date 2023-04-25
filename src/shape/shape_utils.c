/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:34:41 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 20:56:45 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shape.h"
#include "parse.h"
#include "exit.h"
#include "libft.h"

t_shape	*shape_lst_last(t_shape *shapes)
{
	if (shapes == NULL)
		return (NULL);
	while (shapes->next != NULL)
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
		scene->shapes->next = NULL;
		return (scene->shapes);
	}
	else
	{
		tmp = shape_lst_last(scene->shapes);
		tmp->next = (t_shape *)ft_calloc(1, sizeof(t_shape));
		if (tmp->next == NULL)
			put_error_and_exit("Failed to malloc");
		tmp->next->next = NULL;
		return (tmp);
	}
}
