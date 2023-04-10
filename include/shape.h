#ifndef SHAPE_H
# define SHAPE_H

# include "vector.h"

typedef struct s_shape t_shape;

enum e_shape_type
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
};

struct s_shape
{
	enum e_shape_type	type;
	t_shape				*next;
	t_vec3	center;
	t_vec3	orientation;
	double	radius;
};

#endif