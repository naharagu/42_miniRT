#ifndef VECTOR_H
# define VECTOR_H

// 1.入射光ベクトル
// 2.レイのベクトル
// 3.物体上の点における法線ベクトル

typedef struct s_vec3 t_vec3;
struct		s_vec3
{
	double	x;
	double	y;
	double	z;
};


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