#include "vector.h"
#include <math.h>

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_addition(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_subtraction(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_multiply_scalar(t_vec3 a, double b)
{
	return (vec3_create(a.x * b, a.y * b, a.z * b));
}

double	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
//内積

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.y * b.z - a.z - b.y, a.z * b.x - a.x - b.z, a.x * b.y - a.y * b.x));
}
//外積

double	vec3_magnitude(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
//ノルム

t_vec3	vec3_normalize(t_vec3 a)
{
	double mag = vec3_magnitude(a);
	if (mag == 0)
		return (vec3_create(0, 0, 0)); //0除算のエラー処理は不要?
	return (vec3_create(a.x / mag, a.y / mag, a.z / mag));
}
//正規化
