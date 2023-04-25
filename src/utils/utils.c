/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:50:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 18:02:16 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_in_range_double(double num, double min, double max)
{
	if (min <= num && num <= max)
		return (true);
	return (false);
}

bool	is_in_range_int(int num, int min, int max)
{
	if (min <= num && num <= max)
		return (true);
	return (false);
}
