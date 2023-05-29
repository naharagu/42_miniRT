/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:47:34 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/29 12:08:16 by naharagu         ###   ########.fr       */
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

t_color	parse_color(char *str)
{
	t_color	color;
	char	**str_array;

	str_array = ft_split(str, ',');
	if (str_array == NULL)
		put_error_and_exit("Failed to split color");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid color format");
	color.x = ft_atod(str_array[0]);
	color.y = ft_atod(str_array[1]);
	color.z = ft_atod(str_array[2]);
	if (is_in_range_int(color.x, 0, 255) == false
		|| is_in_range_int(color.y, 0, 255) == false
		|| is_in_range_int(color.z, 0, 255) == false)
		put_error_and_exit("Invalid color format");
	free_split(str_array);
	return (color);
}

t_vec3	parse_vec3(char *str)
{
	t_vec3	vec3;
	char	**str_array;

	str_array = ft_split(str, ',');
	if (str_array == NULL)
		put_error_and_exit("Failed to split vector");
	if (count_array(str_array) != 3)
		put_error_and_exit("Invalid vector format");
	vec3.x = ft_atod(str_array[0]);
	vec3.y = ft_atod(str_array[1]);
	vec3.z = ft_atod(str_array[2]);
	free_split(str_array);
	return (vec3);
}
