/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:47 by naharagu          #+#    #+#             */
/*   Updated: 2023/06/06 06:36:46 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "color.h"
# include "main.h"
# include "shape.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_shape	t_shape;
typedef struct s_scene	t_scene;
typedef struct s_window	t_window;
typedef struct s_light	t_light;
typedef struct s_camera
{
	t_vec3				origin;
	t_vec3				dir;
	double				fov;
}						t_camera;

typedef struct s_light
{
	t_vec3				origin;
	double				intensity;
	t_vec3				color;
	t_vec3				dir;
	t_light				*next;
}						t_light;
struct					s_scene
{
	double				ambient_ratio;
	t_vec3				ambient_color;
	t_camera			camera;
	t_light				*lights;
	size_t				lights_num;
	t_shape				*shapes;
};

//parse.c
void					init_scene(t_scene *scene);
void					init_window(t_window *window);
void					parse_rt_file(int argc, char **argv, t_scene *scene);
void					validate_file_name(char *argv);

//parse_ACL.c
void					parse_ambient(char **str_array, t_scene *scene);
void					parse_camera(char **str_array, t_scene *scene);
void					parse_light(char **str_array, t_scene *scene);

//parse_utils.c
void					free_split(char **split);
size_t					count_array(char **str_array);
void					check_normalized(t_vec3 vec);

// parse_vec3.c
bool					check_range_vec3(t_vec3 vec3);
t_vec3					parse_vec3(char *str);

// parse_color.c
size_t					parse_colors(t_shape *shape, char **str_array, size_t index);
t_vec3					parse_color(char *str);

// parse_bump.c
size_t					parse_bump(t_shape *shape, char **str_array, size_t index);

//parse_shape.c
void					parse_sphere(char **str_array, t_scene *scene);
void					parse_plane(char **str_array, t_scene *scene);
void					parse_cylinder(char **str_array, t_scene *scene);
void					parse_cone(char **str_array, t_scene *scene);

#endif
