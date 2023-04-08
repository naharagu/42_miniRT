/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:12:33 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/08 09:12:34 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	calculate_ambient_light(void)
{
	double	k_a;
	double	I_a;
	double	R_a;

	k_a = 0.01;
	I_a = 0.1;
	R_a = k_a * I_a;
	return (R_a);
}
