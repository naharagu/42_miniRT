#ifndef SHAPE_H
# define SHAPE_H

#include "parse.h"
#include "vector.h"
#include "color.h"

typedef struct s_shape t_shape;
typedef struct s_scene t_scene;

enum e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

struct s_shape
{
	enum e_shape_type	type;
	t_shape				*next;
	t_vec3	center;
	t_vec3	orientation;
	double	radius;
	t_color	color;
};

void	init_shape(t_shape *shape);
t_shape	*shape_lst_last(t_shape *shapes);
t_shape	*shape_lst_add(t_scene *scene);

#endif