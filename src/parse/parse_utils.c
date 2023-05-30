/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/29 23:17:43 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exit.h"
#include "libft.h"
#include "utils.h"

void	validate_file_name(char *argv)
{
	if (ft_strlen(argv) < 4)
		put_rtfile_error_and_exit("Invalid file name");
	if (ft_strrchr(argv, '.') == NULL)
		put_rtfile_error_and_exit("Invalid file name");
	if (ft_strncmp(ft_strrchr(argv, '.'), ".rt", 3) != 0)
		put_rtfile_error_and_exit("Invalid file name");
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

size_t	count_array(char **str_array)
{
	size_t	i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}

void	check_normalized(t_vec3 vec)
{
	t_vec3	unit;

	unit = vec3_normalize(vec);
	if (vec3_magnitude(vec) != 1.0)
	{
		printf("for the vector: %f,%f,%f\n", vec.x, vec.y, vec.z);
		printf("the unit vector is: %f,%f,%f\n", unit.x, unit.y, unit.z);
		put_error_and_exit("vector is not normalized");
	}
}
