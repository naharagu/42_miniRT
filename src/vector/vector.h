#ifndef VECTOR_H
# define VECTOR_H

// 1.入射光ベクトル
// 2.レイのベクトル
// 3.物体上の点における法線ベクトル

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_color;
struct		s_vec3
{
	double	x;
	double	y;
	double	z;
};

void		set_color(double r, double g, double b, t_color *color);
int			get_color_in_int(t_color color);

//caluculation
t_vec3	vec3_create(double x, double y, double z);
t_vec3	vec3_addition(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtraction(t_vec3 a, t_vec3 b);
t_vec3	vec3_multiply_scalar(t_vec3 a, double b);
double	vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b);
double	vec3_magnitude(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);

#endif