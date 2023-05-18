/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:04:59 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/18 06:28:23 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3	t_vec3;
struct					s_vec3
{
	double				x;
	double				y;
	double				z;
};

//caluculation
t_vec3					vec3_create(double x, double y, double z);
t_vec3					vec3_addition(t_vec3 a, t_vec3 b);
t_vec3					vec3_subtraction(t_vec3 a, t_vec3 b);
t_vec3					vec3_normalize(t_vec3 a);

//product
t_vec3					vec3_multiply_scalar(t_vec3 a, double b);
double					vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec3					vec3_cross_product(t_vec3 a, t_vec3 b);
double					vec3_magnitude(t_vec3 a);

#endif